#include "OtherFunctions.h"
int Menu(){
    Car obj;
    while(true)
    {
        cout <<endl<< "Choose the option: " << endl << "1)Add characteristics." << endl << "2)Get infornation." << endl
             << "3)Change characteristics." << endl << "4)Close." << endl;
        int choice;
        try
        {
            RightChoice(choice, 4);
        }
        catch(const MyException& ex)
        {
            ex.show();
        }
        catch(...)
        {
            cout<<"Unknown error!"<<endl;
        }
            if (choice == 1)
            {
                AddEngine(obj);
                AddBody(obj);
                AddColor(obj);
                AddBrand(obj);
            }
            else if (choice == 2)
            {
                choice=0;
                cout << "1)Engine parameters." << endl << "2)Body parameters." << endl << "3)Color." << endl
                     << "4)Brand."
                     << endl << endl;
                try
                {
                    RightChoice(choice, 4);
                }
                catch(const MyException& ex)
                {
                    ex.show();
                }
                catch(...)
                {
                    cout<<"Unknown error!"<<endl;
                }
                    if (choice == 1)
                    {
                        FindOutEngine(obj);
                    }
                    else if (choice == 2)
                    {
                        FindOutBody(obj);
                    }
                    else if (choice == 3)
                    {
                        FindOutColor(obj);
                    }
                    else if (choice == 4)
                    {
                        FindOutBrand(obj);
                    }


            }
            else if (choice == 3)
            {
                choice=0;
                cout << "1)Engine parameters." << endl << "2)Body parameters." << endl << "3)Color." << endl
                     << "4)Brand."
                     << endl;
                try {
                    RightChoice(choice, 4);
                }
                catch(const MyException&ex)
                {
                    ex.show();
                }
                catch(...)
                {
                    cout<<"Unknown error!"<<endl;
                }
                    if (choice == 1)
                    {
                        AddEngine(obj);
                    }
                    else if (choice == 2)
                    {
                        AddBody(obj);
                    }
                    else if (choice == 3)
                    {
                        AddColor(obj);
                    }
                    else if (choice == 4)
                    {
                        AddBrand(obj);
                    }
            }
            else if (choice == 4)
            {
                cout << "It was nice to meet you! Goodbye!" << endl;
                break;
            }
    }
    _getch();
    return 0;
}




