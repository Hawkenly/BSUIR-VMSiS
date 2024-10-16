
#include "functions.h"

int main() {
    double start,end;
    int choose;
    FILE*database;
    database=fopen("database.txt","rt");
    if(database==nullptr){
        cout<<"ERROR!"<<endl;
        return 0;
    }
    typedef unordered_map<string ,string>Map;
    Map table;
    while(true){
        cout<<"\nChoose the option:\n1 - Upload N strings from database\n2 - Add a string\n3 - Delete a string\n4 - Find IP\n5 - Print table\n6 - Exit"<<endl;
        check_from_1_to_6(&choose);

        if(choose==1){
            if(table.size()==AMOUNT){
                cout<<"Table is full."<<endl;
                continue;
            }
            int N;
            do {
                cout << "How many strings to upload:" << endl;
                scanf_s("%d", &N);
                if(N+table.size()>AMOUNT)
                    cout<<"Choose N no more than "<<(AMOUNT-table.size())<<endl;
            }while(N+table.size()>AMOUNT);



            for(int i=0;i<N;i++) {
                char*key,*value,*ip;
                upload(database,&key,&value);
                generate_ip(&ip);
                string values;
                values=value;
                values+="\t";
                values+=ip;
                table.insert(Map::value_type(key,values));
            }


        }

        if(choose==2){
            if(table.size()==AMOUNT){
                cout<<"Table is full."<<endl;
                continue;
            }
            string key, value;
            cout<<"Input a key:"<<endl;
            cin>>key;
            cout<<"Input a value"<<endl;
            cin>>value;
            char*ip;
            generate_ip(&ip);
            value+=" ";
            value+=ip;
            table.insert(Map::value_type(key,value));
        }

        if(choose==3){
            start=clock();
            if(table.empty()){
                printf("Table is empty.\n");
                continue;
            }
            string key;
            cout<<"Input a key:"<<endl;
            cin>>key;
            if(table.erase(key))
                cout<<"Success!";
            else
                cout<<"There is no such element."<<endl;
            end=clock();
        }

        if(choose==4){
            if(table.empty()){
                printf("Table is empty.\n");
                continue;
            }
            string key;
            cout<<"Input a key:"<<endl;
            cin>>key;
            auto it =table.find(key);
            if(it!=table.end()) {
                if (it->first == key) {
                    size_t i = 0;
                    while (it->second[i] != '\t')
                        i++;
                    i++;
                    while (it->second[i]) {
                        cout << it->second[i];
                        i++;
                    }
                   continue;
                }
            }
            else
                cout<<"There is no such element."<<endl;
        }

        if(choose==5){
            if(table.empty()){
                printf("Table is empty.\n");
                continue;
            }
            for(auto it=table.begin();it!=table.end();++it){
                cout<<it->first<<" "<<it->second<<endl;
            }
        }

        if(choose==6)
            break;
    }
    fclose(database);

    printf("%.100f",(end-start)/CLOCKS_PER_SEC);

    _getch();
    return 0;
}
