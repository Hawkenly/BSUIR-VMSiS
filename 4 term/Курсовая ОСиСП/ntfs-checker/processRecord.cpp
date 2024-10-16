#include "header.h"

void readRecord(HANDLE h, LONGLONG recordIndex, const std::vector<Run>& MFTRunList,
                ULONG recordSize, ULONG clusterSize, ULONG sectorSize, LPBYTE buffer)
{
    LONGLONG sectorOffset = recordIndex * recordSize / sectorSize;
    ULONG sectorNumber = recordSize / sectorSize;

    for (ULONG sector = 0; sector < sectorNumber; sector++)
    {
        LONGLONG cluster = (sectorOffset + sector) / (clusterSize / sectorSize);
        LONGLONG vcn = 0LL; //виртуальный номер кластера внутри MFT
        LONGLONG offset = -1LL;

        //пробегаемся по списку отрезков MFT
        for (const Run& run : MFTRunList)
        {
            if (cluster < vcn + run.length)
            {
                //смещение относительно начала MFT в байтах
                offset = (run.offset + cluster - vcn) * clusterSize + (sectorOffset + sector) * sectorSize % clusterSize;
                break;
            }
            vcn += run.length;
        }
        if (offset == -1LL)
            throw std::runtime_error("Failed to read file record");

        seek(h, offset);
        ULONG read;
        if (!ReadFile(h, buffer + sector * sectorSize, sectorSize,
                      &read, nullptr) || read != sectorSize)
            throw std::runtime_error("Failed to read file record");
    }
}

void seek(HANDLE h, ULONGLONG position)
{
    LARGE_INTEGER pos;
    pos.QuadPart = (LONGLONG)position;
    LARGE_INTEGER result;
    if (!SetFilePointerEx(h, pos, &result, SEEK_SET) ||
        pos.QuadPart != result.QuadPart)
        throw std::runtime_error("Failed to seek");
}

LPBYTE findAttribute(RecordHeader* record, ULONG recordSize, ULONG typeID)
{
    LPBYTE p = LPBYTE(record) + record->attributeOffset;
    while (true)
    {
        if (p + sizeof(AttributeHeaderR) > LPBYTE(record) + recordSize)
            break;

        auto* header = (AttributeHeaderR*)p;
        if (header->typeID == AT_END)
            break;

        if (header->typeID == typeID && p + header->length <= LPBYTE(record) + recordSize)
            return p;

        p += header->length;
    }
    return nullptr;
}