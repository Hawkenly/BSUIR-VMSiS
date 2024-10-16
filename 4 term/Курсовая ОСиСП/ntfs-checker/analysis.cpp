#include "header.h"

void readBootSector(HANDLE handle, BootSector &bootSector, ULONG &sectorSize,ULONG &clusterSize,
                    ULONG &recordSize, LONGLONG &totalClusters){

    ULONG read;
    if (!ReadFile(handle, &bootSector, sizeof(BootSector), &read,
                  nullptr) || read != sizeof(BootSector)) {
        throw std::runtime_error("Failed to read boot sector");
    }

    if (bootSector.oemID.QuadPart != NTFS_IDENTIFIER) {
        printf("\nVolume is not NTFS. OEM ID: %llu\n", bootSector.oemID.QuadPart);
        throw std::runtime_error("Volume is not NTFS");
    }

    printf("Volume is NTFS. OEM ID: \"%llu\"\n\n", bootSector.oemID.QuadPart);

    if(bootSector.zero0!=0 || bootSector.zero1 !=0 || bootSector.zero2 !=0 || bootSector.zero3 !=0 ||
    bootSector.zero4 !=0 || bootSector.zero5 !=0)
        throw std::runtime_error("Particular bits are not 0.\n");

    sectorSize = bootSector.bytesPerSector;
    clusterSize = sectorSize * bootSector.sectorsPerCluster;
    recordSize = bootSector.clustersPerRecord >= 0 ? bootSector.clustersPerRecord * clusterSize :
                 1 << -bootSector.clustersPerRecord;
    totalClusters = bootSector.totalSectors / bootSector.sectorsPerCluster;
}

void readMFTMain(HANDLE handle, std::vector<Run>& MFTRunList, LONGLONG &MFTSize,
                 std::vector<Run>& BitMapRunList, LONGLONG &BitMapSize, ULONG sectorSize, ULONG clusterSize, ULONG recordSize){

    readRunList(handle, 0, AT_DATA, MFTRunList, sectorSize, clusterSize, recordSize,
                &MFTRunList, &MFTSize);

    readRunList(handle, 0, AT_BITMAP, MFTRunList,sectorSize, clusterSize, recordSize,
                &BitMapRunList, &BitMapSize);
}


void readBitmap(HANDLE handle, const std::vector<Run>& BitMapRunList, ULONG clusterSize, std::vector<UCHAR>& blocks) {
    ULONG read;
    LONGLONG sumClusters = 0;
    for (const Run& run : BitMapRunList) {
        LONGLONG offset = run.offset * clusterSize;
        seek(handle, offset);
        if (!ReadFile(handle, &blocks[0] + sumClusters * clusterSize,
                      run.length * clusterSize, &read,
                      nullptr) || read != run.length * clusterSize)
            throw std::runtime_error("Failed to read BitMap");
        sumClusters += run.length;
    }
}

// Запись в лог
void writeToLog(std::fstream& log, const std::string& volume) {

    int choice;
    bool flag = true;
    std::cout << "Before running, do you want to clear Log.txt file?\n1 - Yes\n2 - No" << std::endl;
    while (flag) {
        std::cin >> choice;
        if (choice == 1 ) {
            log.open("Log.txt", std::ios::out);
            flag = false;
        } else if (choice == 2) {
            log.open("Log.txt", std::ios::app);
            flag = false;
        } else {
            std::cout << "Incorrect input. Try again." << std::endl;
        }
    }

    std::time_t currentTime = std::time(nullptr);
    std::string dateTimeString = std::ctime(&currentTime);
    log << "Integrity checking of volume: " << volume[4] << "\nDate/time: " << dateTimeString << std::endl;
    log << "------------------------------\n";
}

// Запись в файл анализа
void writeToAnalysis(std::ofstream& analysis, const std::string& volume) {
    std::time_t currentTime = std::time(nullptr);
    std::string dateTimeString = std::ctime(&currentTime);
    analysis << "Integrity checking of volume: " << volume[4] << "://\nDate/time: " << dateTimeString;
    analysis << "------------------------------\n";
    analysis << "File List:\n";
}

// Обработка каждой записи
void processRecord(HANDLE handle, const std::vector<Run>& MFTRunList, LONGLONG recordIndex, ULONG recordSize, ULONG clusterSize, ULONG sectorSize,
                   const std::vector<Run>& BitMapRunList, LONGLONG BitMapSize, std::fstream& log, std::ofstream& analysis, bool& errorOccur) {
    std::vector<UCHAR> record(recordSize);
    analysis << recordIndex;
    readRecord(handle, recordIndex, MFTRunList, recordSize, clusterSize, sectorSize, &record[0]);
    auto* recordHeader = (RecordHeader*)&record[0];
    if (memcmp(recordHeader->signature, "FILE", 4) != 0) {
        analysis << "   -\n";
        return;
    }

    if (recordHeader->baseRecord != 0LL) {
        analysis << "   extension for " << recordHeader->baseRecord << std::endl;
        return;
    }

    auto* nameAttr = (AttributeHeaderR*)findAttribute(recordHeader, recordSize, AT_FILE_NAME);

    if (nameAttr == nullptr) {
        analysis << "   Failed to find $File_Name attribute\n";
        return;
    }

    auto* nameContent = (FileName*)((LPBYTE)nameAttr + nameAttr->contentOffset);

    switch (recordHeader->flag) {
        case MFT_RECORD_NOT_USED: {
            log << "File: ";
            for (int i = 0; i < nameContent->nameLength; i++) {
                log << nameContent->name + i * 2;
            }
            log << ". Error: record is not used.\n";
            analysis << "   file ";
            errorOccur = true;
            break;
        }
        case MFT_RECORD_NOT_USED | MFT_RECORD_IS_DIRECTORY: {
            log << "Directory: ";
            for (int i = 0; i < nameContent->nameLength; i++) {
                log << nameContent->name + i * 2;
            }
            log << ". Error: record is not used.\n";
            analysis << "   dir ";
            errorOccur = true;
            break;
        }
        case MFT_RECORD_IN_USE: analysis << "   file ";  break;
        case MFT_RECORD_IN_USE | MFT_RECORD_IS_DIRECTORY: analysis << "   dir ";  break;
        default: analysis << "        "; break;
    }

    for (int i = 0; i < nameContent->nameLength; i++) {
        analysis << nameContent->name + i * 2;
    }

    std::vector<UCHAR> blocks((BitMapSize / clusterSize + 1) * clusterSize);
    readBitmap(handle, BitMapRunList, clusterSize, blocks);

    LONGLONG cluster = recordHeader->MFTRecord * recordSize / clusterSize;
    std::bitset<8> bits = blocks[cluster / 9];
    bool isClusterUsed = bits.test(cluster - 9 * cluster / 9);
    if (!isClusterUsed) {
        analysis << ", ERROR: BitMap error!";
        log << "File: ";
        for (int i = 0; i < nameContent->nameLength; i++) {
            log << nameContent->name + i * 2;
        }
        log << ". Error: Corresponding cluster is not allocated.\n";
        errorOccur = true;
    }
    analysis << "\n";
}

void mainAnalysis(HANDLE handle, const std::vector<Run>& MFTRunList, LONGLONG recordsNumber, const std::vector<Run>& BitMapRunList,
                  LONGLONG BitMapSize, ULONG sectorSize, ULONG clusterSize, ULONG recordSize, const std::string& volume,
                  std::atomic<LONGLONG>& progress, std::atomic<bool>& analysisCompleted) {

    bool  errorOccur = false;
    std::fstream log;
    std::ofstream analysis("Analysis.txt");

    writeToLog(log, volume);
    writeToAnalysis(analysis, volume);

    std::cout<<"\nPlease waiting... Analysis is started.\n"<<std::endl;
    std::thread progressBarThread(progressBar, std::ref(progress), recordsNumber, std::ref(analysisCompleted));
    for (LONGLONG recordIndex = 0; recordIndex < recordsNumber; recordIndex++) {
        progress = recordIndex + 1;
        processRecord(handle, MFTRunList, recordIndex, recordSize, clusterSize, sectorSize, BitMapRunList, BitMapSize, log, analysis,  errorOccur);
    }

    log << "------------------------------\n\n\n\n";
    analysis << "------------------------------\n\n\n\n";
    log.close();
    analysis.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    analysisCompleted = true;

    progressBarThread.join();
    std::cout << "Analysis is finished.\n" << std::endl;
    if (errorOccur) {
        std::cout << "Some errors were found. Please check Log.txt for more information" << std::endl;
    } else {
        std::cout << "There are no errors. Everything is OK." << std::endl;
    }

    std::cout << "Analysis process is located in Analysis.txt in an utility directory.\n" << std::endl;
}

void progressBar(std::atomic<LONGLONG>& progress, LONGLONG recordsNumber, std::atomic<bool>& analysisCompleted) {
    while (!analysisCompleted) {
        int barWidth = 70;
        float progressPercent = (float)progress / (float)recordsNumber;
        std::cout << "[";
        int pos = barWidth * progressPercent;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        int integerPart = (int)(progressPercent * 100.0);
        double fractionalPart = (progressPercent*100.0 - (float)integerPart)*100.0;
        std::cout << "] " << integerPart <<"." << (int)fractionalPart << " %\r";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << std::endl << std::endl;
}

void basicInformation(BootSector bootSector, ULONG sectorSize,ULONG clusterSize, ULONG recordSize,
                      LONGLONG totalClusters, LONGLONG MFTSize, LONGLONG recordsNumber, const std::string& volume) {
    std::fstream log;
    writeToLog(log, volume);

    printf("BASIC INFORMATION ABOUT A VOLUME\n\n");
    printf("Total clusters: %lld, %lld (Bytes)\n", totalClusters, totalClusters * clusterSize);
    printf("Cluster size: %lu (Bytes)\n", clusterSize);
    printf("Total sectors: %llu, %llu (Bytes)\n", bootSector.totalSectors,
           bootSector.totalSectors * sectorSize);
    printf("Sector size: %lu (Bytes)\n", sectorSize);
    printf("Sectors per cluster: %u\n", bootSector.sectorsPerCluster);
    printf("Start MFT cluster: %llu\n", bootSector.MFTCluster);
    printf("MFT size: %llu (Bytes)\n", MFTSize);
    printf("Records number: %llu\n", recordsNumber);
    printf("Record size: %lu (Bytes)\n", recordSize);

    log << "BASIC INFORMATION ABOUT A VOLUME\n";
    log << "------------------------------\n\n\n\n";
    log.close();
}