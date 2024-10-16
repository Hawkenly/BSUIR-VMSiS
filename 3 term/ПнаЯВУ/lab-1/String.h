
class MyString{
    char*string;
    size_t size;
public:
    MyString():size(0),string(nullptr){};
    explicit MyString(char*buf);
    explicit MyString(size_t n);
    MyString(const MyString&str);

    MyString& operator=(const MyString&str);
    friend  MyString operator +(const MyString&str1,const MyString&str2);
    MyString& operator +=(const MyString& str1);
    friend bool operator==(const MyString&str1, const MyString &str2);
    friend bool operator !=(const MyString&str1, const MyString&str2);
    char& operator[](int&);
    MyString operator ()(int,int);

    static void input_2(int& ,int&);
    ~MyString();
    void Print() ;
    static void input_1(int&);

};