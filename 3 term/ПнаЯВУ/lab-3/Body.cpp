#include "Body.h"
#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;

Body::Body(int n, float length, float width, float height) {
    number_of_doors=n;
    size[0]=length;
    size[1]=width;
    size[2]=height;
    cout<<"Constructor Body"<<endl;
}

Body::~Body() {
    cout<<"Destructor Body"<<endl;
}

int Body::GetNumberOfDoors() const {
    return number_of_doors;
}

void Body::SetNumberOfDoors(int n) {
    number_of_doors=n;
}

float* Body::GetSize() {
    return size;
}

void Body::SetSize(float length, float width, float height) {
    size[0]=length;
    size[1]=width;
    size[2]=height;
}

/*void Body::Show() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL,"Russian.UTF-8");
    cout<<"Number of doors: "<<number_of_doors<<endl;
    cout<<"Size: "<<size[0]<<"x"<<size[1]<<"x"<<size[2]<<" м"<<endl;
}*/

