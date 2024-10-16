#include "functions.h"


int main(){
    List*head=NULL;
    List*tail=NULL;
    int fl;
    while(1) {
        printf("Choose:\n1 - Create list\n2 - Add a node\n3 - Delete element\n4 - Sort\n5 - Print list\n6 - Close program\n");
        int choose;
        check_1_2_3_4_5_6(&choose);
        int rc;
        if (choose == 1) {
            if(head!=NULL)
                free_list(&tail,&head);
            int n;
                do {
                    printf("Amount of nodes:\n");
                    rc= scanf_s("%d", &n);
                    fl = check_int();
                } while (fl == -1 || rc!=1 || n<=0);
            create_double_list(&head,&tail, n);
        }
        if(choose==2){

            add_list_to_position(&head,&tail);
        }
        if(choose==3)
            delete_element_on_position(&head,&tail);
        if(choose==4)
            sort(&head,&tail);
        if(choose==5)
            print_list(head);
        if (choose == 6)
            break;
    }
    free_list(&tail,&head);
    _getch();
    return 0;
}
