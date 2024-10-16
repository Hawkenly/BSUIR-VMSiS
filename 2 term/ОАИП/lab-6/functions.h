#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct list {
    int num;
    struct list *next;
    struct list *prev;
}List;

int check_int();
void check_1_2_3_4_5_6(int*choose);
void create_double_list(List**head,List**tail,int n);
void add_list_to_position(List**head,List**tail);
void delete_element_on_position(List**head, List**tail);
void free_list(List**tail,List**head);
void sort(List **head,List**tail);


void create_double_list(List**head,List**tail,int n){ //добавление в конец;
    printf("Input nums:\n");
        while (n > 0) {
            List *temp = (struct list *) malloc(sizeof(struct list));
            temp->next = NULL;
            temp->prev = NULL;
            int fl,rc;
            do{
            rc=scanf_s("%d",&temp->num);
            fl=check_int();
                }while(fl==-1 || rc!=1);

            List*t=*tail;
            int repeat=0;
            while(t!=NULL){
                if(t->num==temp->num) {
                    repeat=1;
                    break;
                }
             t=t->prev;
            }
            if(repeat!=1) {
                if (*head == NULL) {
                    *head = temp;
                    *tail = temp;
                } else {
                    List *p = *tail;
                    p->next = temp;
                    temp->prev = p;
                    *tail = temp;
                }
            }
            n--;
        }
}

void add_list_to_position(List**head,List**tail){
    if(*head==NULL){
        printf("List wasn't created.\n");
        return;
    }
    int number,fl,rc;
    do {
        printf("Input a position to add an element:\n");
        rc= scanf_s("%d", &number);
        fl = check_int();
    } while (fl == -1 || rc!=1 || number<1);
    number--;
    List*temp;
    temp=(struct list*)malloc(sizeof(struct list));
    temp->next=NULL;
    temp->prev=NULL;
    printf("Input a num:\n");
    do{
        rc=scanf_s("%d",&temp->num);
        fl=check_int();
    }while(fl==-1 || rc!=1);
    List*p=*head;
    int repeat=0;
    while(p!=NULL){
        if(p->num==temp->num) {
            repeat = 1;
            break;
        }
        p=p->next;
    }
    p=*head;
    if(repeat!=1) {
        int i = number;
        while (p->next != NULL && i > 1) {
            p = p->next;
            i--;
        }
        if (number == 0) {
            temp->next=*head;
            (*head)->prev=temp;
            *head=temp;
        }
        else{
            if(p->next!=NULL)
                p->next->prev=temp;
            if(p->next==NULL)
                *tail=temp;
            temp->next=p->next;
            p->next=temp;
            temp->prev=p;
        }
    }
}

void sort(List **head,List**tail){
    if(*head==NULL){
        printf("List wasn't created.\n");
        return;
    }
    List *p1=*head;
    List *p2=(*head)->next;
    List*p3=*head;
    while(p3!=NULL) {
        while (p1 != NULL && p2 != NULL) {
            if(p1->num>p2->num){
                if(p1==*head)
                    *head=p2;
                if(p2->next!=NULL)
                    p2->next->prev=p1;
                else
                    *tail=p1;
                p1->next=p2->next;

                p2->next=p1;
                p2->prev=p1->prev;

                if(p1->prev!=NULL)
                    p1->prev->next=p2;
                p1->prev=p2;

                p2=p1->next;
            }
            else{
                p1=p1->next;
                p2=p2->next;
            }
        }
        p1=*head;
        p2=(*head)->next;
        p3=p3->next;
    }
}

int check_int(){
    char ch, i=0;
    while((ch=(char)getchar())!='\n'){
        if(ch<'0'|| ch>'9' ){
            printf("Wrong input\n");
            fflush(stdin);
            return -1;
        }
        i++;
    }
    return 1;
}

void check_1_2_3_4_5_6(int*choose){
    int sr ;
    do {
        scanf_s("%d", choose);
        sr = check_int();
        if (sr == 1) {
            if (*choose < 1 || *choose > 6) {
                printf("Wrong input\n");
                sr = -1;
                fflush(stdin);
            }
        }
    } while (sr == -1);
    fflush(stdin);
}

void print_list(List *head){
    if(head==NULL){
        printf("List is empty.\n");
        return;
    }
    List*p=head;
    while(p!=NULL) {
        printf("% d ", p->num);
        p = p->next;
        /*if(p!=NULL)
            printf("-->");
    }*/
    }
    printf("\n");

}

void free_list(List**tail,List**head){
    List*p;
    p=*tail;
    while(p!=*head){
        free(p);
        p=p->prev;
    }
    free(*head);
}

void delete_element_on_position(List**head, List**tail){
    if(*head==NULL){
        printf("List wasn't created.\n");
        return;
    }
    int number,fl,rc;
    do {
        printf("Input a position of an element to delete:\n");
        rc= scanf_s("%d", &number);
        fl = check_int();
    } while (fl == -1 || rc!=1 || number<1);
    number--;
    List*p;
    p=*head;
    int i = number;
    while (p->next != NULL && i > 1) {
        p = p->next;
        i--;
    }
    if (number == 0) {
       *head=(*head)->next;
       free(p);
    }
    else{
        if(p->next!=NULL){
            p->next->prev=p->prev;
            p->prev=p->next;
            free(p);
        }
        else if(p->next==NULL) {
            *tail = (*tail)->prev;
            (*tail)->next = NULL;
            free(p);
        }

    }



}
