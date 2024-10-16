#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
typedef struct FILO{
    char element;
    struct FILO *next;
}stack;

void push(stack**head,char c);
void pop(stack**head);
void get_str(char**str);
void rpn(char*str,char **str_out,stack**head);
int priority(char c);
int if_num(char c);
int empty(stack**head);
void add_memory(char**str_out,int *n);
int check_str(const char*str);

void push(stack**head,char c){
    stack*temp=(stack*)malloc(sizeof(stack));
    temp->element=c;
    temp->next=NULL;
    if(*head==NULL){
        *head=temp;
    }
    else{
        temp->next=*head;
        *head=temp;
    }
}

void pop(stack**head){
    stack *temp=*head;
    if(*head!=NULL){
        *head=(*head)->next;
        free(temp);
    }
}

void get_str(char**str){
    printf("Input an expression with integers\n");
    char buf[255];
    fgets(buf,253,stdin);
    size_t len;
    len=strlen(buf);
    buf[len-1]='\0';
    if(buf[len-2]=='+' || buf[len-2]=='-' || buf[0]=='+' || buf[0]=='-'){
        printf("Incorrect sings\n");
        _getch();
        exit(1);
    }
    *str=(char*)calloc(strlen(buf)+1,sizeof(char));
    strcpy(*str,buf);
    int i=0;
    while((*str)[i]!='\0'){
        if(((*str)[i]=='+'||(*str)[i]=='-'||(*str)[i]=='*'||(*str)[i]=='/')&&((*str)[i+1]=='+' || (*str)[i+1]=='-'|| (*str)[i+1]=='*'|| (*str)[i+1]=='/')){
            printf("Incorrect signs\n");
            _getch();
            exit(1);
        }
        i++;
    }
}

int check_str(const char*str){
    int i=0;
    while(str[i]!='\0'){
        if((str[i]>='0' && str[i]<='9') || (str[i]=='+' || str[i]=='(' || str[i]==')' ||str[i]=='-' || str[i]=='/' || str[i]=='*'));
        else{
            printf("Incorrect expression. Please input again.\n");
            fflush(stdin);
            return 1;
        }
        i++;
    }
    return 0;
}
void rpn(char*str,char **str_out,stack**head){
    int i=0,j=0;
    int n=0;
    while(str[i]!='\0'){
        if(if_num(str[i])==1){
            while(if_num(str[i])==1) {  //если операнд
                if (n == 0) {              //добавляем в выходную строку
                    n++;
                    (*str_out) = (char *) malloc(n * sizeof(char));
                    (*str_out)[j] = str[i];
                    j++;
                } else {
                    add_memory(str_out, &n);
                    (*str_out)[j] = str[i];
                    j++;
                }
                i++;
            }
            add_memory(str_out, &n);
            (*str_out)[j] = ' ';
            j++;
            i--;
        }
        else if(if_num(str[i])==0){  //если операция
            if(empty(head)==1 || str[i]=='(')   //если скобка или стек пустой, добавляем в стек
                push(head,str[i]);
            else if(str[i]==')'){       //если закрывающая скобка, добавляем в выходную строку все операнды до открывающей
                while((*head)->element!='('){
                    add_memory(str_out,&n);
                    (*str_out)[j]=(*head)->element;
                    pop(head);
                    j++;
                }
                pop(head);
            }
            else{                      //если стек не пустой, смотрим на приоритет операций
                int pri1= priority(str[i]);
                int pri2= priority((*head)->element);
                if(pri1>pri2)         //если приоритет входящей больше, добавляем в стек
                    push(head,str[i]);
                else{                 //если приоритет входящей <=, добавляем стековые в выходную строку
                    while(pri1<=pri2 && empty(head)==0){
                        add_memory(str_out,&n);
                        (*str_out)[j]=(*head)->element;
                        pop(head);
                        if(empty(head)==0)
                            pri2= priority((*head)->element);
                        j++;
                    }
                    push(head,str[i]);
                }
            }

        }
        i++;
    }
    while(empty(head)!=1){  //проверка на остаток в стеке
        add_memory(str_out,&n);
        (*str_out)[j]=(*head)->element;
        pop(head);
        j++;
    }
    add_memory(str_out,&n);
    (*str_out)[j]='\0';
    int k=0;
    while((*str_out)[k]!='\0'){
        if((*str_out)[k]=='(' || (*str_out)[k]==')'){
            printf("Incorrect brackets\n");
            _getch();
            exit(1);
        }
        k++;
    }
}

int priority(char c){  //Приоритет операций
    if(c=='+' || c=='-')
        return 2;
    if(c=='(')
        return 1;
    if(c=='/' || c=='*')
        return 3;
    return -1;
}

int if_num(char c){
    if(c>='0' && c<='9')
        return 1;
    else
        return 0;
}

int empty(stack**head){ //Проверка стека на пустоту
    stack*temp;
    temp=*head;
    if(temp==NULL)
        return 1;
    else
        return 0;

}

void add_memory(char**str_out,int *n){
    (*n)++;
    *str_out=(char*)realloc(*str_out,(*n)*sizeof(char));
}