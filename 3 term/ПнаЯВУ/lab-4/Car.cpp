#include "Car.h"

using namespace std;

Car::Car(const char *br, type tp, float v, int p, int n, float length, float width, float height, const char *clr) : Engine(tp,v,p),Body(n,length,width,height),Color(clr)
{
    strcpy_s(brand,strlen(br)+1,br);
}

char* Car::getBrand()
{
    return brand;
}

void Car::setBrand(const char *br)
{
    strcpy_s(brand,strlen(br)+1,br);
}

Car& Car::operator=(const Car &right){
    if (this == &right)
        return *this;
    Body::operator=(right);
    Engine::operator=(right);
    Color::operator=(right);
    strcpy_s(brand, strlen(right.brand) + 1, right.brand);
    return *this;
}

std::ostream& operator << (std::ostream &os,const Car&car)
{
    std::string str;
    (car.tp==diesel)? str="diesel":(car.tp==petrol)? str="petrol": (car.tp==rotary)? str="rotary":(car.tp==hybrid)? str="hybrid": str="unknown";
    os<<fixed;
    return os<<"Type: "+str<<std::endl<<
             "Volume: "<<setprecision(2)<<car.volume<<std::endl<<
             "Power: "<<car.power<<std::endl<<
             "Amount of doors: "<<car.number_of_doors<<std::endl<<
             "Size: "<<setprecision(2)<<car.size[0]<<" x " <<setprecision(2)<< car.size[1]<<" x "<< setprecision(2)<<car.size[2]<<std::endl<<
             "Color: "+static_cast<std::string>(car.color)<<std::endl<<
             "Brand: "+static_cast<std::string>(car.brand)<<std::endl;
}

Car& operator >> (std::istream & is, Car& car)
{
    char buf[255];
    Engine engine;
    Body body;
    Color color;

    is>>engine;
    is>>body;
    is>>color;
    is>>buf;
    is>>buf;

    car.setVolume(engine.getVolume());
    car.setPower(engine.getPower());
    car.setTp(engine.getTp());

    car.setNumberOfDoors(body.getNumberOfDoors());
    car.setSize(body.getSize());

    car.setColor(color.getColor());

    car.setBrand(buf);

    return car;
}

bool Car::operator<(const Car &obj) const
{
    if(strcmp(brand,obj.brand)<0)
        return true;
    return false;

}

void Car::writeToBin(std::ostream & os)
{
    os.write(reinterpret_cast<char*>(this),sizeof(Car));
}

void Car::readFromBin(std::istream & is)
{
    is.read(reinterpret_cast<char*>(this),sizeof(Car));
}
