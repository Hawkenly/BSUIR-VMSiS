#include "Engine.h"
#include "Body.h"
#include "Color.h"

class Car :public Engine,public Body,public Color{
private:
    char brand[255]={};
public:
    Car():Engine(),Body(),Color(),brand{"Unknown"}{};
    explicit Car(const char*,type,float,int,int,float,float,float,const char*);

    Car& operator =(const Car& right);
    friend std::ostream& operator << (std::ostream& ,const Car& );
    friend Car& operator >> (std::istream& , Car&);
    bool operator <(const Car&) const;
    void writeToBin(std::ostream &);
    void readFromBin(std::istream &);

    char* getBrand();
    void setBrand(const char*);

};

