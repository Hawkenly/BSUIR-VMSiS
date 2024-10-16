#include "Engine.h"

using namespace std;

Engine::Engine(type t, float v, int p)
{
    tp=t;
    volume=v;
    power=p;
}

type Engine::getTp() const
{
    return tp;
}

void Engine::setTp(const char*str)
{
    if((string) str == "petrol")
        tp=petrol;
    else if((string) str == "diesel")
        tp=diesel;
    else if((string) str == "rotary")
        tp=rotary;
    else if((string) str == "hybrid")
        tp=hybrid;
}

void Engine::setTp(type tp_)
{
    tp=tp_;
}

float Engine::getVolume() const
{
    return volume;
}

void Engine::setVolume(float v)
{
    volume=v;
}

int Engine::getPower() const
{
    return power;
}

void Engine::setPower(int p)
{
    power=p;
}

Engine& Engine::operator=(const Engine &right)
{
    if(this==&right)
        return *this;
    tp=right.tp;
    volume=right.volume;
    power=right.power;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Engine& engine)
{
    std::string str;
    (engine.tp==diesel)? str="diesel":(engine.tp==petrol)? str="petrol": (engine.tp==rotary)? str="rotary":(engine.tp==hybrid)? str="hybrid": str="unknown";
    os<<fixed;
    return os<<"Type: "+str<<std::endl<<
                "Volume: "<<setprecision(2)<<engine.volume<<std::endl<<
                "Power: "<<engine.power<<std::endl;
}

Engine& operator>>(std::istream & is, Engine&engine)
{
    char buf[255];
    int power;
    float volume;
    is>>buf;
    is>>buf;
    engine.setTp(buf);
    is>>buf;
    is>>volume;
    engine.setVolume(volume);
    is>>buf;
    is>>power;
    engine.setPower(power);
    return engine;
}

bool Engine::operator<(const Engine &obj)
{
    return power<obj.power;
}

void Engine::writeToBin(std::ostream & os)
{
    os.write(reinterpret_cast<char*>(this),sizeof(Engine));
}

void Engine::readFromBin(std::istream & is)
{
    is.read(reinterpret_cast<char*>(this),sizeof(Engine));
}

