#include "functions.h"

int main() {
    tree *node = NULL;
    int n, choice, sr,rc;
    while (1) {
        printf("\nChoose the right option:\n1 - Add elements\n2 - Find element\n3 - Delete element\n4 - Change element\n5 - Output a tree\n6 - Distance between nodes\n7 - Stop\n");
        check_7(&choice);
        if (choice == 1) {
            int col;

            printf("How many elements add?\n");
            do {
                sr = scanf_s("%d", &col);
                rc = check_int();
            } while (sr == 0|| rc==-1);
            for(int i=0;i<col;i++) {
                do {
                    printf("Input a value\t");
                    sr = scanf_s("%d", &n);
                    rc=check_int();
                } while (sr ==0 || rc==-1);
                create_tree(&node, n);
            }
        }

        if (choice == 2) {
            do {
                printf("Input a value\t");
                sr = scanf_s("%d", &n);
                check_int();
            } while (sr == -1);

                tree *p;
                p=find_element(node, n);
                if(p!=NULL)
                    printf("Your element %d was found",p->num);
            }

            if (choice == 3) {
                do {
                    printf("Input a value\t");
                    sr = scanf_s("%d", &n);
                    check_int();
                } while (sr == -1);
                    node=delete_element(node, n);
            }
            if(choice==4) {
                do {
                    printf("Input a value\t");
                    sr = scanf_s("%d", &n);
                    check_int();
                } while (sr == -1);
                change_element(node,node, n);
            }
            if (choice == 5)
                print(node);
            if(choice==6){
                findDistance(node);
            }
            if (choice == 7)
                break;

        }
        _getch();
        return 0;
    }
