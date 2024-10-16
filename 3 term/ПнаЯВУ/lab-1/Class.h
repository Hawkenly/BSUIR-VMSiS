#include <iostream>
#include <conio.h>
#include <cstring>
using namespace std;


class Time{
    int hour, minute, second;
public:
    Time(int, int ,int);
    void SetTime(int, int, int);
    void printTime() const;
    void printTime(int) const;
   // void printTimeDefault() const;
    void GetH() const;
    void GetM() const;
    void GetS() const;

    static void input(int& );

    friend void operator+(const Time&obj);
    friend void operator&(Time&obj1,int h);

    ~Time();
};


