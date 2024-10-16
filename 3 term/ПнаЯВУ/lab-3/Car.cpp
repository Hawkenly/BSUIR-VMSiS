#include "Car.h"
#include <iostream>
#include <cstring>
#include <conio.h>
using namespace std;

Car::Car(const char *br, type tp, float v, int p, int n, float length, float width, float height, const char *clr) : Engine(tp,v,p),Body(n,length,width,height),Color(clr){
    strcpy_s(brand,strlen(br)+1,br);

    cout<<"Constructor Car"<<endl;
}

Car::~Car(){
    cout<<"Destructor Car"<<endl;
}

char* Car::GetBrand() {
    return brand;
}

void Car::SetBrand(const char *br) {
    strcpy_s(brand,strlen(br)+1,br);

}

/*void Car::Show() {

        Engine::Show();
        Body::Show();
        Color::Show();
        cout << "Brand: " << brand << endl;

}*/


