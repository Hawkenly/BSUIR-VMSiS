#pragma once

#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <winioctl.h>
#include <shellapi.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <bitset>
#include <thread>
#include <atomic>
#include <iomanip>

#define NTFS_IDENTIFIER 0x202020205346544E
static_assert(true);

#pragma pack(push, 1)
struct BootSector
{
    UCHAR       jump[3];
    ULARGE_INTEGER       oemID;
    WORD        bytesPerSector;
    UCHAR       sectorsPerCluster;
    USHORT      zero0;
    UCHAR       zero1;
    USHORT      zero2;
    USHORT      zero3;
    UCHAR       mediaDescriptor; //0xf8 = hard disk
    USHORT      zero4;
    WORD        sectorsPerTrack; //unused
    WORD        heads; //unused
    DWORD       hiddenSectors;  //unused
    ULONG       zero5;
    UCHAR       unused0[4];
    LONGLONG    totalSectors;
    LONGLONG    MFTCluster;
    LONGLONG    MFTMirrCluster;
    CHAR        clustersPerRecord;
    UCHAR       unused1[3];
    CHAR        clustersPerIndex;
    UCHAR       unused2[3];
    LONGLONG    serialNumber;
    DWORD       checkSum;
    UCHAR       bootCode[0x1aa];
    UCHAR       endMarker[2];
};

struct RecordHeader
{
    UCHAR       signature[4];
    USHORT      updateSeqOffset;
    USHORT      updateSeqNumber;
    LONGLONG    lsn;
    USHORT      sequenceNumber;
    USHORT      hardLinkCount;
    USHORT      attributeOffset;
    USHORT      flag;
    ULONG       usedSize;
    ULONG       allocatedSize;
    LONGLONG    baseRecord;
    USHORT      nextAttributeID;
    USHORT      unused;
    ULONG       MFTRecord;
};

struct AttributeHeaderR
{
    ULONG       typeID;
    USHORT      length;
    USHORT      reserved;
    UCHAR       formCode;
    UCHAR       nameLength;
    USHORT      nameOffset;
    USHORT      flag;
    USHORT      attributeID;
    ULONG       contentLength;
    USHORT      contentOffset;
    WORD        unused;
};

struct AttributeHeaderNR
{
    ULONG       typeID;
    USHORT      length;
    USHORT      reserved;
    UCHAR       formCode;
    UCHAR       nameLength;
    USHORT      nameOffset;
    USHORT      flag;
    USHORT      attributeID;
    LONGLONG    startVCN;
    LONGLONG    endVCN;
    USHORT      runListOffset;
    USHORT      compressionUnit;
    UCHAR       unused[4];
    LONGLONG    allocatedContentSize;
    LONGLONG    contentSize;
    LONGLONG    initializedContentSize;
};

struct FileName
{
    LONGLONG    parentDirectory;
    LONGLONG    dateCreated;
    LONGLONG    dateModified;
    LONGLONG    dateMFTModified;
    LONGLONG    dateAccessed;
    LONGLONG    allocatedSize;
    LONGLONG    usedSize;
    ULONG       flag;
    ULONG       reparseValue;
    UCHAR       nameLength;
    UCHAR       nameType;
    UCHAR       name[];
};

#pragma pack(pop)

struct Run
{
    LONGLONG    offset;
    LONGLONG    length;
    Run() : offset(0LL), length(0LL) {}
    Run(LONGLONG offset, LONGLONG length) : offset(offset), length(length) {}
};

typedef enum {
    MFT_RECORD_NOT_USED	    = 0,
    MFT_RECORD_IN_USE		= 1,
    MFT_RECORD_IS_DIRECTORY	= 2,
} MFT_RECORD_FLAGS;

typedef enum
{
    AT_FILE_NAME				= 0x30,
    AT_DATA						= 0x80,
    AT_BITMAP					= 0xb0,
    AT_END						= 0xffffffff
} ATTR_TYPES;

//runList.cpp
void readRunList(HANDLE handle, LONGLONG recordIndex, ULONG typeID, const std::vector<Run>& MFTRunList, ULONG sectorSize,
                 ULONG clusterSize, ULONG recordSize, std::vector<Run>* runList, LONGLONG* contentSize);
std::vector<Run> parseRunList(LPBYTE runList);

//processRecord.cpp
void readRecord(HANDLE h, LONGLONG recordIndex, const std::vector<Run>& MFTRunList,ULONG recordSize, ULONG clusterSize,
                ULONG sectorSize, LPBYTE buffer);
void seek(HANDLE h, ULONGLONG position);
LPBYTE findAttribute(RecordHeader* record, ULONG recordSize, ULONG typeID);


//analysis.cpp
void readBootSector(HANDLE handle, BootSector &bootSector, ULONG &sectorSize,ULONG &clusterSize,
                    ULONG &recordSize, LONGLONG &totalClusters);
void readMFTMain(HANDLE handle, std::vector<Run>& MFTRunList, LONGLONG &MFTSize,
                 std::vector<Run>& BitMapRunList, LONGLONG &BitMapSize, ULONG sectorSize, ULONG clusterSize, ULONG recordSize);
void basicInformation(BootSector bootSector, ULONG sectorSize,ULONG clusterSize, ULONG recordSize,
                      LONGLONG totalClusters, LONGLONG MFTSize, LONGLONG recordsNumber, const std::string& volume);
void mainAnalysis(HANDLE handle, const std::vector<Run>& MFTRunList, LONGLONG recordsNumber, const std::vector<Run>& BitMapRunList,
                  LONGLONG BitMapSize, ULONG sectorSize, ULONG clusterSize, ULONG recordSize, const std::string& volume,
                  std::atomic<LONGLONG>& progress, std::atomic<bool>& analysisCompleted);
void processRecord(HANDLE handle, const std::vector<Run>& MFTRunList, LONGLONG recordIndex, ULONG recordSize, ULONG clusterSize, ULONG sectorSize,
                   const std::vector<Run>& BitMapRunList, LONGLONG BitMapSize, std::fstream& log, std::ofstream& analysis, bool& errorOccur);
void readBitmap(HANDLE handle, const std::vector<Run>& BitMapRunList, ULONG clusterSize, std::vector<UCHAR>& blocks);
void writeToLog(std::fstream& log, const std::string& volume);
void writeToAnalysis(std::ofstream& analysis, const std::string& volume);
void progressBar(std::atomic<LONGLONG>& progress, LONGLONG recordsNumber, std::atomic<bool>& analysisCompleted);