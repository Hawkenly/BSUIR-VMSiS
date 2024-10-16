#include "String.h"

MyString::MyString(char*buf){
    size=strlen(buf);
    string=new char[size+1];
    strcpy_s(string,(size+1)*sizeof(char),buf);

}
MyString::MyString(size_t n){
    size=n;
    string=new char[size+1];
}

MyString::MyString(const MyString&str){
    size=str.size;
    string=new char[size+1];
    strcpy_s(string,(size+1)*sizeof(char),str.string);
    //cout<<"Copy operator :) :) :)"<<endl;
}

MyString::~MyString(){
    delete[] string;
}

MyString& MyString:: operator=(const MyString&str){
    if(this==&str)          //проверка на самоприсваивание
        return *this;
    delete []string;
    size=str.size;
    string=new char[size+1];
    strcpy_s(string,(size+1)*sizeof(char),str.string);
    return *this;
}

MyString operator+(const MyString&str1, const MyString&str2){
    MyString str(str1.size+str2.size);
    strcpy_s(str.string,(str1.size+1)*sizeof(char),str1.string);
    strcat(str.string,str2.string);
    return str;
}

MyString& MyString::operator+=(const MyString &str1) {
    size+=str1.size;
    strcat(string,str1.string);
    return *this;
}

bool operator==(const MyString&str1, const MyString&str2){
    if(strcmp(str1.string,str2.string)==0)
        return true;
    else
        return false;
}

bool operator !=(const MyString&str1, const MyString &str2){
    if(strcmp(str1.string,str2.string)!=0)
        return true;
    else
        return false;
}

MyString MyString:: operator()(int a,int b){
    if(a<0)
        a=0;
    if(b>size)
        b=(int)size;
    MyString str(b-a+1);
    int j,i;
    for(i=a,j=0;i<=b;i++,j++)
        str.string[j]=string[i];
    str.string[j]='\0';

    return str;
}

char& MyString::operator[](int &i){
    if(i>size){
        return string[0];
    }
    return string[i];
}

void MyString::Print() {
    cout<<string<<endl;
}

void  MyString:: input_2(int&a,int&b) {
    while(true) {
        cin >> a>>b;
        while (!cin) {
            cout << "Please, enter again" << endl;
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cin >> a>>b;
        }
        if(a>b) {
            cout<<"a have to be fewer than b"<<endl;
            continue;
        }
        break;
    }
}

void MyString:: input_1(int&value) {
    cin>>value;
    while(!cin){
        cout<<"Please, enter again"<<endl;
        cin.clear();
        while(cin.get()!='\n')
            continue;
        cin>>value;
    }
}

void task_S() {
    while (true) {
        fflush(stdin);
        cout << "Input first string" << endl;
        char buf[256];
        cin.getline(buf,254);
        MyString str1(buf);
        cout << "Input second string" << endl;
        cin.getline(buf,254);
        MyString str2(buf);
        cout << "Choose the right option:" << endl << "1)=" << endl << "2)+" << endl << "3)+=" << endl << "4)==" << endl
             << "5)!=" << endl<<"6)[]"<<endl << "7)()(int,int)" << endl << "8)Exit." << endl;
        int choice;
        check_choice(choice, 8);
        if (choice == 1) {
            str1 = str2;
            cout << "Result:" << endl;
            str1.Print();
        }
        if (choice == 2) {
            MyString str =str1+str2;
            cout << "Result:" << endl;
            str.Print();
        }
        if (choice == 3) {
            str1 += str2;
            cout << "Result:" << endl;
            str1.Print();
        }
        if (choice == 4) {
            bool res = (str1 == str2);
            if (!res)
                cout << "Strings are not equal" << endl;
            else
                cout << "String are equal" << endl;
        }
        if (choice == 5) {
            bool res = (str1 != str2);
            if (!res)
                cout << "Strings are equal" << endl;
            else
                cout << "String are not equal" << endl;
        }
        if(choice==6){
            char element;
            int num;
            cout<<"Choose the position "<<endl;
            MyString::input_1(num);
            element=str1[num];
            cout<<"The element is "<<element<<endl;
            str2[num]=element;
            cout<<"The element is "<<element<<endl;
        }
        if (choice == 7) {
            cout << "Choose the interval: a=?,b=?" << endl;
            int a, b;
            MyString::input_2(a,b);
            MyString str_1 = str1(a, b);
            MyString str_2 = str2(a, b);
            cout << "Result str1: ";
            str_1.Print();
            cout << "Result str2: ";
            str_2.Print();
        }
        if (choice == 8) {
            cout << "Thanks for testing. :)" << endl;
            break;
        }

        cout << "Continue?" << endl << "1)Yes" << endl << "2)No" << endl;
        check_choice(choice, 2);
        if (choice == 2) {
            cout << "Thanks for testing. :)" << endl;
            break;
        } else
            continue;
    }

    _getch();
}
