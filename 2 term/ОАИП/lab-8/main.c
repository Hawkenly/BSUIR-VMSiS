#include "functions.h"

int main() {
    int choose;
    double start,end;
    FILE*database;
    database=fopen("database.txt","rt");
    Hash_table *table= create_table(CAPACITY);
    while(1) {
        printf("\nChoose the option:\n1 - Upload N strings from database\n2 - Add a string\n3 - Delete a string\n4 - Find IP\n5 - Print table\n6 - Exit\n");
        check_from_1_to_6(&choose);
        if(choose==1){
            int N;
            printf("Choose how many strings upload:\n");
            scanf_s("%d",&N);

            upload(database,table,N);
        }
        if(choose==2)
            add_str(table);

        if(choose==3) {
            start=clock();
            delete_item(table);
            end=clock();
        }
        
        if(choose==4)
            print_item(table);


        if(choose==5)
            printf_table(table);

        if(choose==6)
            break;

    }
    fclose(database);
    free_table(table);

    printf("%.100f",(end-start)/CLOCKS_PER_SEC);
    _getch();
    return 0;
}