#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

class vector2f      {
    private:
        float x;
        float y;

    public:
         vector2f(float r=0, float i=0 )
        {
            x = r; y = i;
        }
        void out() const
        {
            cout <<"x = "<< x << " , " <<"y = "<< y <<  endl;
        }
        friend vector2f operator + (const vector2f &c1,const  vector2f &c2); //принимает в качестве параметра ссылку на объект
        friend vector2f operator - (const vector2f &c1, const vector2f &c2);
        friend vector2f operator / (const vector2f &c1, const vector2f &c2);
        friend vector2f operator * (const vector2f &c1, const vector2f &c2);


        vector2f& operator += (const vector2f &c)
        {   x+=c.x;
            y+=c.y;
            return *this; //указатель на текущий объект
        }
    vector2f& operator -= (const vector2f &c)
    {   x-=c.x;
        y-=c.y;
        return *this;
    }
    vector2f& operator *= (const vector2f &c)
    {   x*=c.x;
        y*=c.y;
        return *this;
    }
    vector2f& operator /= (const vector2f &c)
    {
        if(c.x==0 || c.y==0){
            cout<<"Operation cant be implemented\n"<<endl;
            _getch();
            exit(1);
        }
        x/=c.x;
        y/=c.y;
        return *this;
    }
};

vector2f operator + (const vector2f &c1,const vector2f &c2)
{
    vector2f temp;
    temp.x = c1.x + c2.x;
    temp.y = c1.y + c2.y;
    return(temp);
}

vector2f operator - (const vector2f &c1, const vector2f &c2)
{
    vector2f temp;
    temp.x=c1.x-c2.x;
    temp.y=c1.y-c2.y;
    return(temp);
}

vector2f operator / (const vector2f &c1, const vector2f &c2)
{
    vector2f temp;
    if(c2.x==0 || c2.y==0){
        cout<<"Operation cant be implemented\n"<<endl;
        _getch();
        exit(1);
    }
    temp.x =c1.x/c2.x;
    temp.y=c1.y/c2.y;
    return(temp);
}

vector2f operator * (const vector2f &c1, const vector2f &c2)
{
    vector2f temp;
    temp.x=c1.x*c2.x;
    temp.y=c1.y*c2.y;
    return(temp);
}



int main()
{
    while(1) {
        vector2f c;
        float x, y;
        cout << "Input x,y for class a:" << endl ;
        cout <<"x : ";
        cin >> x ;
        cout <<"y : ";
        cin>> y;
        vector2f a(x, y);
        cout << "Input x,y for class b:" << endl;
        cout <<"x : ";
        cin >>x;
        cout <<"y : ";
        cin >>y;
        vector2f b(x, y);
        cout << "Choose operator:" << endl;
        string oper;
        cin >> oper;
        if (oper == "+") {
            c = a + b;
            c.out();
        }
        else if (oper == "-") {
            c = a - b;
            c.out();
        }
        else if (oper == "*") {
            c = a * b;
            c.out();
        }
        else if (oper == "/") {
            c = a / b;
            c.out();
        }
        else if (oper == "+=") {
            a += b;
            a.out();
        }
        else  if (oper == "-=") {
            a -= b;
            a.out();
        }
        else if (oper == "*=") {
            a *= b;
            a.out();
        }
        else if (oper == "/=") {
            a /= b;
            a.out();
        }
        else{
            cout<<"Incorrect operator\n"<<endl;
        }
        cout <<"Continue?\n1 - Yes\n2 - No" <<endl;
        int n;
        cin>>n;
        if(n==2)
            break;
    }
    _getch();
    return 0;
}