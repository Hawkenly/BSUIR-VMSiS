#include "Engine.h"
#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

Engine::Engine(type t, float v, int p) {
    tp=t;
    volume=v;
    power=p;
    cout<<"Constructor Engine"<<endl;
}

Engine::~Engine() {
    cout<<"Destructor Engine"<<endl;
}

type Engine::GetTp() {
    return tp;
}

void Engine::SetTp(const char*str) {
    if((string) str == "petrol")
        tp=petrol;
    else if((string) str == "diesel")
        tp=diesel;
    else if((string) str == "rotary")
        tp=rotary;
    else if((string) str == "hybrid")
        tp=hybrid;
}

float Engine::GetVolume() const{
    return volume;
}

void Engine::SetVolume(float v) {

    volume=v;
}

int Engine::GetPower() const {
    return power;
}

void Engine::SetPower(int p) {
    power=p;
}

/*void Engine::Show() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL,"Russian.UTF-8");
    switch(tp){
        case Nothing: cout<<"Type of engine: Nothing"<<endl; break;
        case One: cout<<"Type of engine: One"<<endl; break;
        case Two: cout<<"Type of engine: Two"<<endl; break;
        case Three: cout<<"Type of engine: Three"<<endl; break;
        case Four: cout<<"Type of engine: Four"<<endl; break;
        default: ;
    }
    cout<<"Volume: "<<volume<<" л"<<endl;
    cout<<"Power: "<<power<<" Вт"<<endl;
}*/
