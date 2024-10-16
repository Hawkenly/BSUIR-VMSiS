#include "header.h"

int main(/*int argc, char**argv*/){

    log_("Program was launched.");
    /*if(argc!=3){
        printf("Enter like this:\n 'name.exe' 'dividend' 'divisor'\n");
        exit(1);
    }*/
    int choose;
    /* printf("Do u want to find a remainder of the division?(P.s. a divisor need to be a degree of 2 and lower than 128 )\n1 - Yes\n2 - No\n");
     check_1_or_2(&choose);
     if(choose==1)
         Remainder(argv[1],argv[2]);*/
    Events*event=NULL;
    Events*root=NULL;

    int choice;
    while(1) {
        printf("\n------------------------\n");
        printf("Choose u want:\n1 - Add\n2 - Find event\n3 - Delete event\n4 - Sort\n5 - Output\n6 - Close\n");
        check_1_2_3_4_5_6(&choose);
        fflush(stdin);
        if (choose == 1) {
            int fl=0;
            while(1) {
                if (root == NULL) {
                    fl=1;
                    root = init();
                    log_("List was initilised.");
                }
                printf("------------------------\n");
                if(fl==1) {
                    printf("Add one more event?\n1 - Yes\n2 - No\n");
                    check_1_or_2(&choice);
                    if (choice == 2)
                        break;
                }
                Events *ptr = root;
                int i = 0;
                while (ptr != NULL) {
                    i++;
                    event = ptr;
                    ptr = ptr->next;
                }
                add_elem(&event, i);
                fl=1;
                log_("The %d event was added",i);
            }
        }
        if(choose==2){
            printf("Choose how to find:\n1 - By name\n2 - By new field\n");
            check_1_or_2(&choose);
            if(choose==1)
                find_event_default(&root);
            else
                find_event_new(&root);
        }
        if(choose==3) {
            delete_elem(&root);
        }
        if(choose==4) {
            printf("Choose what to sort:\n1 - Default fields\n2 - New field\n");
            check_1_or_2(&choose);
            if(choose ==1) {
                sort_default(&root);
                output_list(&root);
                log_("List was successfully sorted.");
            }
            else{
                sort_new(&root);
                output_list(&root);
                log_("List was successfully sorted.");
            }

        }
        if(choose==5) {
            output_list(&root);
            log_("List was printed.");
        }
        if(choose==6)
            break;
    }

    log_("Program was closed.");


    _getch();
    return 0;

}