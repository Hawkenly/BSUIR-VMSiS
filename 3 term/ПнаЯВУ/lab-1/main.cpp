#include "Class.cpp"
#include "String.cpp"

int main() {
    int choice;
    cout<<"Choose the option:"<<endl<<"1)Time"<<endl<<"2)MyString"<<endl;
    check_choice(choice,2);
    if(choice==1)
        task_T();
    if(choice==2)
        task_S();
    return 0;
}