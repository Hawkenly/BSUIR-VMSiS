#include "Color.h"
#include <iostream>

using namespace std;

Color::Color(const char *clr)
{
    strcpy_s(color,strlen(clr)+1,clr);
}

const char* Color::getColor() const
{
    return color;
}

void Color::setColor(const char *clr)
{
    strcpy_s(color,strlen(clr)+1,clr);
}

Color& Color::operator=(const Color &right)
{
    if(this==&right)
        return *this;
    strcpy_s(color,strlen(right.color)+1,right.color);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Color& color)
{
    return os<<"Color: "+static_cast<std::string>(color.color)<<std::endl;
}

Color& operator>>(std::istream & is, Color& color)
{
    char buf[255];
    is>>buf;
    is.getline(buf,255);
    std::string buf_str=static_cast<std::string>(buf);
    buf_str.erase(0,1);

    color.setColor(buf_str.c_str());
    return color;
}

bool Color::operator<(const Color &obj)
{
    return (strcmp(color,obj.color)<0);
}

void writeToBin(std::ostream & os, Color& color)
{
    os.write(reinterpret_cast<char*>(&color),sizeof(Color));
}

void readFromBin(std::istream & is, Color& color)
{
    is.read(reinterpret_cast<char*>(&color),sizeof(Color));
}
