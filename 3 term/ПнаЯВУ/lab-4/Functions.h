#include <climits>

using namespace std;

void RightChoice(int& choice,int m)
{
    cin>>choice;
    if(!cin || choice<1 || choice>m)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        throw InputException(001, "Incorrect choice.");
    }
}

template <typename T>
void check_for_each(T element)
{
    std::cout<<element<<std::endl;
}


/*template <typename T>
void CheckInput(T &value,T left,T right)
{
    cin>>value;
    if(!cin)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        throw InputException(010, "Incorrect data! Please try again.");
    }
    if(value<left || value>right)
    {
        ostringstream oss;
        oss<<left;
        std::string l=oss.str();
        oss.str("");
        oss<<right;
        std::string r=oss.str();
        throw std::range_error("Range error! The range is "+l+" - "+r);
    }
}*/


/*void AddEngine(Car&obj)
{
    float volume;
    int power;
    char type[255];
    try
    {
        cout << "Input engine's volume: ";
        CheckInput(volume,static_cast<float>(0.5),static_cast<float>(5.0));
        obj.setVolume(volume);

        cout << "Input engine's power: ";
        CheckInput(power,50,2000);
        obj.setPower(power);
    }
    catch(const MyException&ex)
    {
        ex.show();
        AddEngine(obj);
    }
    catch(const std::range_error&ex)
    {
        cout<<ex.what()<<std::endl;
        AddEngine(obj);
    }

    cout<<"Choose engine's type: ";
    //fflush(stdin);
    cin.ignore();
    cin.getline(type, 254);
    obj.setTp(type);
}

void AddBody(Car&obj)
{
    int number;
    float length,height,width;
    try
    {
        cout << "Input amount of doors: ";
        CheckInput(number,1,6);
        obj.setNumberOfDoors(number);

        cout << "Input body's size: ";
        cout << "Length: ";
        CheckInput(length,static_cast<float>(3.5),static_cast<float>(16.0));

        cout << "Height: ";
        CheckInput(width,static_cast<float>(1.5),static_cast<float>(2.5));

        cout << "Height: ";
        CheckInput(height,static_cast<float>(1.4),static_cast<float>(3.0));

        obj.setSize(length, width, height);
    }
    catch(const MyException&ex)
    {
        ex.show();
        AddBody(obj);
    }
    catch(const std::range_error&ex)
    {
        cout<<ex.what()<<std::endl;
        AddBody(obj);
    }
}

void AddColor(Car&obj){

    char color[255],colorf[255];
    int flag=1;
    cout<<"Input car's color: ";
    while(flag) {
        fflush(stdin);
        cin.getline(color,254);
        try {
            ifstream file("Colors.txt");
            if (file.is_open()) {
                while (file.getline(colorf, 254)) {
                    if (strcmp(colorf, color) == 0) {
                        flag = 0;
                        break;
                    }
                    flag = -1;
                }
            } else
                throw ReadFileException(100, "Unable to open a file.");
            file.close();
        }
        catch(const ReadFileException&ex)
        {
            ex.show();
            AddColor(obj);
        }
        if(flag==-1){
            cout<<"Incorrect color!"<<endl;
            flag=1;
        }
    }
    obj.setColor(color);
}

void AddBrand(Car&obj){
    char brand[255],brandf[255];
    int flag=1;
    cout<<"Input car's brand: ";
    while(flag) {
        fflush(stdin);
        cin.getline(brand,254);
        try {
            ifstream file("Brands.txt");

            if (file.is_open()) {
                while (file.getline(brandf, 254)) {
                    if (strcmp(brandf, brand) == 0) {
                        flag = 0;
                        break;
                    }
                    flag = -1;
                }
            }
            else
                throw ReadFileException(100, "Unable to open a file.");
            file.close();
        }
        catch(const ReadFileException&ex)
        {
            ex.show();
            AddBody(obj);
        }
        if(flag==-1){
            cout<<"Incorrect brand!"<<endl;
            flag=1;
        }
    }
    obj.setBrand(brand);
}*/
