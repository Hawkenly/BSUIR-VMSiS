#include "header.h"

void readRunList(HANDLE handle, LONGLONG recordIndex, ULONG typeID, const std::vector<Run>& MFTRunList, ULONG sectorSize,
                 ULONG clusterSize, ULONG recordSize, std::vector<Run>* runList, LONGLONG* contentSize)
{
    std::vector<UCHAR> record(recordSize);
    readRecord(handle, recordIndex, MFTRunList, recordSize, clusterSize, sectorSize, &record[0]);
    auto* recordHeader = (RecordHeader*)&record[0];
    auto* headerNR = (AttributeHeaderNR*)findAttribute(recordHeader, recordSize, typeID);

    if (headerNR == nullptr)
        return ;
    if (headerNR->formCode == 1)
    {
        std::vector<Run> runListTmp = parseRunList(LPBYTE(headerNR) + headerNR->runListOffset);

        runList->resize(runListTmp.size());
        for (size_t i = 0; i < runListTmp.size(); i++)
            (*runList)[i] = runListTmp[i];

        if (contentSize != nullptr)
            *contentSize = headerNR->contentSize;
    }
}

std::vector<Run> parseRunList(LPBYTE runList)
{
    std::vector<Run> result;

    LONGLONG offset = 0LL; //LCN

    LPBYTE p = runList;
    while (*p != 0x00)
    {
        int lenLength = *p & 0xf;  //кол-во байт на длину
        int lenOffset = *p >> 4;   //кол-во байт на смещение
        p++;

        ULONGLONG length = 0;
        for (int i = 0; i < lenLength; i++)
            length |= *p++ << (i * 8);

        LONGLONG offsetDiff = 0;  //VCN
        for (int i = 0; i < lenOffset; i++)
            offsetDiff |= *p++ << (i * 8);
        if (offsetDiff >= (1LL << ((lenOffset * 8) - 1)))
            offsetDiff -= 1LL << (lenOffset * 8);

        offset += offsetDiff;  //преобразование VCN в LCN: складываем пред. LCN с VCN

        result.emplace_back(offset, length);
    }

    return result;
}

