#include <iostream>
#include <iomanip>

class Body {
protected:
    int number_of_doors;
    float size[3];
public:
    Body():number_of_doors(0),size{0.0,0.0,0.0}{};
    explicit Body(int ,float,float, float);

    Body& operator=(const Body&);
    friend std::ostream& operator<<(std::ostream& , const Body& );
    friend Body& operator>>(std::istream&, Body&);
    bool operator<(const Body&);
    void writeToBin(std::ostream &);
    void readFromBin(std::istream &);


    int getNumberOfDoors() const ;
    void setNumberOfDoors(int);

    const float* getSize() const;
    void setSize(float,float,float);
    void setSize(const float*);

};

