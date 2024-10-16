#include <iostream>
#include <cstring>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include <limits>
#include <fstream>
#include <sstream>

#include "Car.h"
#include "InputException.h"
#include "ReadFileException.h"

using namespace std;

void RightChoice(int& choice,int m)
{
    cin>>choice;
    if(!cin || choice<1 || choice>m)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        throw InputException(1, "Incorrect choice.");
    }
}



template <typename T>
void CheckInput(T &value,T left,T right)
{
    cin>>value;
    if(!cin)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        throw InputException(10, "Incorrect data! Please try again.");
    }
    if(value<left || value>right)
    {
        ostringstream oss;
        oss<<left;
        std::string l=oss.str();
        oss.str("");
        oss<<right;
        std::string r=oss.str();
        throw std::range_error("Range error! The range is "+l+" - "+r);
    }
}

void AddEngine(Car&obj)
{
    float volume;
    int power;
    char type[255];
    try
    {
        cout << "Input engine's volume: ";
        CheckInput(volume,static_cast<float>(0.5),static_cast<float>(5.0));
        obj.SetVolume(volume);

        cout << "Input engine's power: ";
        CheckInput(power,50,2000);
        obj.SetPower(power);
    }
    catch(const MyException&ex)
    {
        ex.show();
        AddEngine(obj);
    }
    catch(const std::range_error&ex)
    {
        cout<<ex.what()<<std::endl;
        AddEngine(obj);
    }

    cout<<"Choose engine's type: ";
    //fflush(stdin);
    cin.ignore();
    cin.getline(type, 254);
    obj.SetTp(type);
}

void AddBody(Car&obj)
{
    int number;
    float length,height,width;
    try
    {
        cout << "Input amount of doors: ";
        CheckInput(number,1,6);
        obj.SetNumberOfDoors(number);

        cout << "Input body's size: ";
        cout << "Length: ";
        CheckInput(length,static_cast<float>(3.5),static_cast<float>(16.0));

        cout << "Height: ";
        CheckInput(width,static_cast<float>(1.5),static_cast<float>(2.5));

        cout << "Height: ";
        CheckInput(height,static_cast<float>(1.4),static_cast<float>(3.0));

        obj.SetSize(length, width, height);
    }
    catch(const MyException&ex)
    {
        ex.show();
        AddBody(obj);
    }
    catch(const std::range_error&ex)
    {
        cout<<ex.what()<<std::endl;
        AddBody(obj);
    }
}

void AddColor(Car&obj){

    char color[255],colorf[255];
    int flag=1;
    cout<<"Input car's color: ";
    while(flag) {
        fflush(stdin);
        cin.getline(color,254);
        try {
            ifstream file("Colors.txt");
            if (file.is_open()) {
                while (file.getline(colorf, 254)) {
                    if (strcmp(colorf, color) == 0) {
                        flag = 0;
                        break;
                    }
                    flag = -1;
                }
            } else
                throw ReadFileException(100, "Unable to open a file.");
            file.close();
        }
        catch(const ReadFileException&ex)
        {
            ex.show();
            AddColor(obj);
        }
        if(flag==-1){
            cout<<"Incorrect color!"<<endl;
            flag=1;
        }
    }
    obj.SetColor(color);
}

void AddBrand(Car&obj){
    char brand[255],brandf[255];
    int flag=1;
    cout<<"Input car's brand: ";
    while(flag) {
        fflush(stdin);
        cin.getline(brand,254);
        try {
            ifstream file("Brands.txt");

            if (file.is_open()) {
                while (file.getline(brandf, 254)) {
                    if (strcmp(brandf, brand) == 0) {
                        flag = 0;
                        break;
                    }
                    flag = -1;
                }
            }
            else
                throw ReadFileException(100, "Unable to open a file.");
            file.close();
        }
        catch(const ReadFileException&ex)
        {
            ex.show();
            AddBody(obj);
        }
        if(flag==-1){
            cout<<"Incorrect brand!"<<endl;
            flag=1;
        }
    }
    obj.SetBrand(brand);
}

void FindOutEngine(Car&obj){
    double volume;
    int power;
    type tp;
    volume=obj.GetVolume();
    power=obj.GetPower();
    tp=obj.GetTp();
    cout<<"Engine's information"<<endl;
    cout<<"------------------------"<<endl;
    cout<<"Engine's volume: "<<volume<<" l"<<endl;
    cout<<"Engine's power: "<<power<<" h.p."<<endl;
    cout<<"Engine's type: ";
    switch(tp){
        case unknown: cout<<"Unknown"<<endl; break;
        case petrol: cout<<"Petrol"<<endl; break;
        case diesel: cout<<"Diesel"<<endl; break;
        case rotary: cout<<"Rotary"<<endl; break;
        case hybrid: cout<<"Hybrid"<<endl; break;
    }
}

void FindOutBody(Car&obj){
    int num;
    float size[3];
    num=obj.GetNumberOfDoors();
    for(int i=0;i<3;i++)
        size[i]=obj.GetSize()[i];
    cout<<"Body's information"<<endl;
    cout<<"------------------------"<<endl;
    cout<<"Amount of doors: "<<num<<endl;
    cout<<"Body's size: "<<size[0]<<"x"<<size[1]<<"x"<<size[2]<<" м"<<endl;
}

void FindOutColor(Car&obj){
    char color[255];
    strcpy_s(color,254,obj.GetColor());
    cout<<"Color's information"<<endl;
    cout<<"------------------------"<<endl;
    cout<<"Car's color: "<<color<<endl;
}

void FindOutBrand(Car&obj){
    char brand[255];
    strcpy_s(brand,254,obj.GetBrand());
    cout<<"Brand's information"<<endl;
    cout<<"------------------------"<<endl;
    cout<<"Car's brand: "<<brand<<endl;
}

