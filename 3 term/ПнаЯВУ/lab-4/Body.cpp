#include "Body.h"

using namespace std;

Body::Body(int n, float length, float width, float height) {
    number_of_doors=n;
    size[0]=length;
    size[1]=width;
    size[2]=height;
}

int Body::getNumberOfDoors() const {
    return number_of_doors;
}

void Body::setNumberOfDoors(int n) {
    number_of_doors=n;
}

const float* Body::getSize() const{
    return size;
}

void Body::setSize(float length, float width, float height) {
    size[0]=length;
    size[1]=width;
    size[2]=height;
}

void Body::setSize(const float* size_)
{
    size[0]=size_[0];
    size[1]=size_[1];
    size[2]=size_[2];
}

Body& Body::operator=(const Body&right)
{
    if(this==&right)
        return *this;
    number_of_doors=right.number_of_doors;
    size[0]=right.size[0];
    size[1]=right.size[1];
    size[2]=right.size[2];
    return *this;
}

std::ostream& operator<<(std::ostream& os,const Body& body)
{
    os<<fixed;
    return os<<"Amount of doors: "<<body.number_of_doors<<std::endl<<
                "Size: "<<setprecision(2)<<body.size[0]<<" x "<<setprecision(2)<< body.size[1]<<" x "<<setprecision(2)<<body.size[2]<<std::endl;
}

Body& operator>>(std::istream& is,Body& body)
{
    char buf[101];
    int num;
    float size[3];
    is.getline(buf,100,':');
    is>>num;
    body.setNumberOfDoors(num);
    for(float & i : size)
    {
        is>>buf;
        is>>i;
    }
    body.setSize(size[0],size[1],size[2]);
    return body;
}

bool Body::operator<(const Body &obj)
{
    return size[0]*size[1]*size[2]<obj.size[0]*obj.size[1]*obj.size[2];
}

void Body::writeToBin(std::ostream & os)
{
    os.write(reinterpret_cast<char*>(this),sizeof(Body));
}

void Body::readFromBin(std::istream & is)
{
    is.read(reinterpret_cast<char*>(this),sizeof(Body));
}
