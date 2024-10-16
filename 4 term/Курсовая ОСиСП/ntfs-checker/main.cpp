#include "header.h"

int main(int argc, char*argv[]) {
    BootSector bootSector{};
    ULONG sectorSize;
    ULONG clusterSize;
    ULONG recordSize;
    LONGLONG totalClusters;
    LONGLONG recordsNumber;
    HANDLE handle = nullptr;
    std::string volume = R"(\\.\_:)";
    std::vector<Run> MFTRunList, BitMapRunList;
    LONGLONG MFTSize = 0LL, BitMapSize = 0LL;
    std::atomic<LONGLONG> progress(0);
    std::atomic<bool> analysisCompleted(false);
    try {
        if (argc == 3 && strlen(argv[1]) == 1 && strlen(argv[2]) == 2 && argv[2][0] == '-') {
            volume[4] = argv[1][0];
            handle = CreateFile(volume.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                nullptr, OPEN_EXISTING, 0, nullptr);
            if (handle == INVALID_HANDLE_VALUE)
                throw std::runtime_error("Failed to open a drive.");
            switch (argv[2][1]) {
                case 'i': {
                    readBootSector(handle, bootSector, sectorSize, clusterSize, recordSize, totalClusters);
                    MFTRunList.assign(1, Run(bootSector.MFTCluster, 24 * recordSize / clusterSize));
                    readMFTMain(handle, MFTRunList, MFTSize, BitMapRunList, BitMapSize, sectorSize, clusterSize,
                                recordSize);
                    recordsNumber = MFTSize / recordSize;

                    basicInformation(bootSector, sectorSize, clusterSize, recordSize,
                                     totalClusters, MFTSize, recordsNumber, volume);
                    system("pause");
                    break;
                }
                case 'f': {
                    readBootSector(handle, bootSector, sectorSize, clusterSize, recordSize, totalClusters);
                    MFTRunList.assign(1, Run(bootSector.MFTCluster, 24 * recordSize / clusterSize));
                    readMFTMain(handle, MFTRunList, MFTSize, BitMapRunList, BitMapSize, sectorSize, clusterSize,
                                recordSize);
                    recordsNumber = MFTSize / recordSize;

                    mainAnalysis(handle, MFTRunList, recordsNumber, BitMapRunList, BitMapSize, sectorSize,
                                 clusterSize, recordSize, volume, progress, analysisCompleted);
                    system("pause");
                    break;
                }
                default:
                    throw std::runtime_error(
                            "Invalid parameters.\nFormat: file.exe disk_letter(C,D,F) parameter(-i,-f)\n -i - general information about a volume\n -f - checking integrity\n");
            }
        } else {
            std::cout << "Format: ntfs_checker disk_letter(C,D,F) parameter(-i, -f)" << std::endl <<
                      "-i - general information about a volume" << std::endl << "-f - checking integrity" << std::endl;
            system("pause");
        }
    }
    catch (std::exception &obj) {
        printf("Error: %s\n", obj.what());
        system("pause");
    }
    catch (...) {
        printf("Error: Unknown\n");
        system("pause");
    }

    if (handle != nullptr)
        CloseHandle(handle);

    return 0;
}
