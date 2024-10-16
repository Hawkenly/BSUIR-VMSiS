#include <limits>
#include <fstream>
#include <algorithm>

#include "Car.h"
#include "InputException.h"
#include "ReadFileException.h"
#include "Queue.h"
#include "Functions.h"
#include "Algorithm.h"


void menu() {
    bool flag=true;
    Car car("Audi",diesel,3.4,700,4,5.0,2.0,2.0,"Green");
    Car car1("Lamborgini",diesel,4.0,1500,2,4.0,2.1,2.1, "Yellow");
    Car car2("Ferrari",hybrid,3.7,1400,4,3.5,2.2,1.5,"Blue");
    /*Engine engine(hybrid,4.0,1200);
    Body body(4,2.5,2.5,2.5);
    Color color("Green");
    Car car0;*/
    Queue<Car> qu={car2,car,car1};
    /*Queue<Car>::iterator iter1=qu.begin();
    Queue<Car>::iterator iter2=qu.end();
    car0=sss::search(iter1,iter2,2);
    std::cout<<car0;*/
    Queue<Car>::iterator it1,it2;
    it1=qu.begin();
    it2=qu.end();

/*    Queue<Car>::reverse_iterator rIt1,rIt2;
    rIt1=qu.rbegin();
    rIt2=qu.rend();
    for(rIt1;rIt1!=rIt2;rIt1++)
        std::cout<<*rIt1<<std::endl;*/


    int a=sss::count(it1,it2);
    std::cout<<"Amount of elements: "<< a<<std::endl;
    std::cout<<qu;

    //sss::for_each(it1,it2);

    while(flag)
    {
        std::cout << "\nChoose the option:\n"
                     "1)Add element\n"
                     "2)Delete element\n"
                     "3)Checks size\n"
                     "4)Check empty\n"
                     "5)Get all elements\n"
                     "6)Clear queue\n"
                     "7)Print queue\n"
                     "8)Write to text file\n"
                     "9)Write to bin file\n"
                     "10)Read from text file\n"
                     "11)Read from bin file\n"
                     "12)Exit" << std::endl;

        int choice;
        try
        {
            RightChoice(choice, 12);
        }
        catch(MyException& exception)
        {
            exception.show();
        }
        switch (choice)
        {
            case 1:
            {
                try
                {
                    qu.push(car1);
                }
                catch(std::bad_alloc& exception)
                {
                    std::cout<<"Allocation error: "<<exception.what()<<std::endl;
                }
                catch(std::exception& exception)
                {
                    std::cout<<"Unknown error."<<std::endl;
                }
                   break;
            }
            case 2:
            {
                try {
                    Car car_del = qu.pop();
                    std::cout << "Deleted element: " << std::endl;
                    std::cout << car_del << std::endl;
                }
                catch(std::out_of_range& exception)
                {
                    std::cout<<"Out of range error: "<<exception.what()<<std::endl;
                }
                catch(std::exception& exception)
                {
                    std::cout<<"Unknown error."<<std::endl;
                }
                break;
            }
            case 3:
            {
                unsigned size=qu.size();
                std::cout<<"Size = "<<size<<std::endl;
                break;
            }
            case 4:
            {
                bool empty=qu.empty();
                if(empty)
                    std::cout<<"Queue is empty!"<<std::endl;
                else
                    std::cout<<"There is at least 1 element"<<std::endl;
                break;
            }
            case 5:
            {
                std::vector<Car> vec;
                vec = qu.peek();
                std::cout<<"Elements:"<<std::endl;
                for (const auto &element: vec)
                    std::cout << element;
                break;
            }
            case 6:
            {
                qu.clear();
                break;
            }
            case 7:
            {
               qu.print();
               break;
            }
            case 8:
            {
                try {
                    std::fstream file("test.txt", std::ios::out);
                    if (file.fail())
                        throw ReadFileException(10,"Open text file error!");
                    file << qu;
                    file.close();
                }
                catch(MyException& exception)
                {
                    exception.show();
                }
                break;
            }
            case 9:
            {
                try {
                    std::fstream file("testBin.bin", std::ios::out | std::ios::binary);
                    if (file.fail())
                        throw ReadFileException(01,"Open bin file error!");
                    qu.writeToBin(file);
                    file.close();
                }
                catch(MyException& exception)
                {
                    exception.show();
                }
                break;
            }
            case 10:
            {
                try {
                    std::fstream file("test.txt", std::ios::in);
                    if (file.fail())
                        throw ReadFileException(10,"Open text file error!");
                    file >> qu;
                    file.close();
                }
                catch(MyException& exception)
                {
                    exception.show();
                }
                break;
            }
            case 11:
            {
                try {
                    std::fstream file("testBin.bin", std::ios::in | std::ios::binary);
                    if (file.fail())
                        throw ReadFileException(01,"Open bin file error!");
                    qu.readFromBin(file);
                    file.close();
                }
                catch(MyException& exception)
                {
                    exception.show();
                }
                break;
            }
            case 12:
            {
                flag=false;
                break;
            }
        }
    }

}