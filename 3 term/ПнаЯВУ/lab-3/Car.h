#include "Engine.h"
#include "Body.h"
#include "Color.h"

class Car :public Engine,public Body,public Color{

    char brand[255]={};
public:
    Car():Engine(),Body(),Color(),brand{"Неизвестно"}{};
    explicit Car(const char*,type,float,int,int,float,float,float,const char*);

    char* GetBrand();
    void SetBrand(const char*);

    //void Show();


    ~Car();
};

