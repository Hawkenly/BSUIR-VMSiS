#include <iostream>
#include <iomanip>

enum type{unknown,petrol,diesel,rotary,hybrid};

class Engine {
protected:
    type tp;
    float volume;
    int power;
public:
    Engine():tp(),volume(0.0),power(0){};
    explicit Engine(type,float,int);

    Engine& operator=(const Engine&);
    friend std::ostream& operator << (std::ostream& ,const Engine& );
    friend Engine& operator>> (std::istream &, Engine&);
    bool operator<(const Engine&);
    void writeToBin(std::ostream &);
    void readFromBin(std::istream &);

    type getTp() const;
    void setTp(const char*);
    void setTp(type);

    float getVolume() const;
    void setVolume(float);

    int getPower() const;
    void setPower(int);

};


