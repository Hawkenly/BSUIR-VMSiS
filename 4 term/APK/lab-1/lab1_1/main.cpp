#include <windows.h>
#include <iostream>

HANDLE COM1;
HANDLE COM2;

void writeToCOM1()
{
    char data = 'A';
    DWORD size = sizeof(data);
    DWORD writtenBytes;
    //             имя           буфер                    размер записи            переменная записи
    WriteFile(COM1, &data, size, &writtenBytes, nullptr);

    std::cout << writtenBytes << " Bytes sended." << std::endl;
}

void readFromCOM2()
{
    DWORD size;
    char data;
    //             имя           буфер                 размер чтения          переменная чтения
    ReadFile(COM2, &data, 1, &size, nullptr);
    std::cout << size << " Bytes received." << std::endl;
    if (size > 0)
    {
        std::cout << data;
    }
}

int main()
{
    //открытие COM-портов
    //                              имя                  режим доступа             совм.доступ         защита                      автосоздание файла                         //шаблон для создания
    COM1 = ::CreateFile("COM1", GENERIC_WRITE, 0, nullptr, OPEN_EXISTING,0, nullptr);
    COM2 = ::CreateFile("COM2", GENERIC_READ, 0, nullptr, OPEN_EXISTING, 0, nullptr);

    if (COM1 == INVALID_HANDLE_VALUE)
    {
       std::cout<<"Opening COM error!"<<std::endl;
       return 0;
    }

    DCB settings;  //основные настройки COM-порта
    settings.DCBlength = sizeof(settings);
    if (!GetCommState(COM1, &settings))
    {
        std::cout << "Getting state error.\n";
    }
    settings.BaudRate = CBR_9600;    //speed
    settings.ByteSize = 8;           //amount bits
    settings.StopBits = ONESTOPBIT;  //amount stopbits
    settings.Parity = NOPARITY;
    if (!SetCommState(COM2, &settings))  //установка конфигурации
    {
        std::cout << "Error setting serial port state.\n";
    }

    writeToCOM1();
    readFromCOM2();

    return 0;
}