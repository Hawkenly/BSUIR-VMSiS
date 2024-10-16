#include "Color.h"
#include <iostream>
#include <cstring>
using namespace std;

Color::Color(const char *clr) {
    strcpy_s(color,strlen(clr)+1,clr);
    cout<<"Constructor Color"<<endl;
}

Color::~Color() {
    cout<<"Destructor Color"<<endl;
}

char* Color::GetColor() {
    return color;
}

void Color::SetColor(const char *clr) {
    strcpy_s(color,strlen(clr)+1,clr);
}

/*void Color::Show() {
    cout<<"Color: "<<color<<endl;
}*/
