#include <iostream>
#include <cstring>

class Color {
protected:
    char color[255];
public:
    Color():color{"Unknown"}{};
    explicit Color(const char*);

    Color& operator=(const Color&);
    friend std::ostream& operator<<(std::ostream& ,const Color& );
    friend Color& operator>>(std::istream &, Color&);
    bool operator <(const Color&);
    friend void writeToBin(std::ostream&, Color&);
    friend void readFromBin(std::istream &, Color&);

    const char* getColor() const;
    void setColor(const char*);

};
