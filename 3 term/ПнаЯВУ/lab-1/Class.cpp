
#include "Class.h"

Time::Time(int h, int m, int s) {
    hour=h;
    minute=m;
    second=s;
    SetTime(h,m,s);
}

void Time::SetTime(int hr, int min, int sec) {
    cout << "Input hours." << endl;
    input(hr);
    while(hr<0 || hr>24)
        input(hr);
    hour=hr;

    cout << "Input minutes." << endl;
    input(min);
    while(min<0 || min>59)
        input(min);
    minute=min;

    cout << "Input seconds." << endl;
    input(sec);
    while(sec<0 || sec>59)
        input(sec);
    second=sec;

}



void Time:: printTime() const {
    cout<<hour<<" hours "<<minute<<" minutes "<<second<<" seconds "<<endl;
}

/*void Time::printTimeDefault() const {
    cout<<((hour==0 || hour==12) ? 0: hour%12)<<":"<<minute<<":"<<second<<((hour<12) ? " AM" : " PM")<<endl;
}*/

void Time::printTime(int a) const {
    cout<<((hour==0 || hour==12) ? 0: hour%12)<<":"<<minute<<":"<<second<<((hour<12) ? " AM" : " PM")<<endl;
}

void Time::GetH() const {
    cout<<"It's "<<hour<<" hours now."<<endl;
}
void Time::GetM() const {
    cout<<"It's "<<minute<<" minutes now."<<endl;
}
void Time::GetS() const {
    cout<<"It's "<<second<<" seconds now."<<endl;
}
Time::~Time() {
    cout<<"Cleaning..."<<endl;
}

void Time:: input(int&value) {
    cin>>value;
    while(!cin){
        cout<<"Please, enter again"<<endl;
        cin.clear();
        while(cin.get()!='\n')
            continue;
        cin>>value;
    }
}

void operator+(const Time&obj){
    obj.printTime();
}

void operator&(Time&obj,int h){
    obj.hour=h;
    obj.minute=0;
    obj.second=0;
}


void check_choice(int&choice,int m){
    cin>>choice;
    while(!cin || choice<1 || choice>m){
        cin.clear();
        while(cin.get()!='\n')
            continue;
        cin>>choice;
    }
}


void task_T() {
     while(true) {
    int h=0, m=0, s=0;
    Time time(h, m, s);
    cout << "Choose the right option:" << endl << "1)Print time." << endl << "2)Print time in default format."
         << endl << "3)Get hours." << endl << "4)Get minutes." << endl << "5)Get seconds." << endl;
    int choice;
    check_choice(choice,5);

    switch (choice) {
        case 1:
            time&0;   //обнуление времени
            +time;    //вывод времени
            break;
        case 2:
            time.printTime(0);    //вывод в default формате
            break;
        case 3:
            time.GetH();
            break;
        case 4:
            time.GetM();
            break;
        case 5:
            time.GetS();
            break;

    }
    cout<<"Choose:"<<endl<<"1)Finish."<<endl<<"2)Continue."<<endl;
    check_choice(choice,2);
    if(choice==1)
        break;
    else
        continue;
}
}