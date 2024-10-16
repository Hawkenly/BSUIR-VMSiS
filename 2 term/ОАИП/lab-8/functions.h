#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define CAPACITY 701 // Size of the Hash Table

typedef struct Hash_Item{
    char*key;
    char*value;
    char*ip;
}Ht_item;

typedef struct List{
    Ht_item *item;
    struct List*next;
    struct List*prev;
}List;


typedef struct Hash_Table{
    Ht_item**items;
    List**lists;
    int size;
    int count;
}Hash_table;



size_t hash_function(const char* str);
Ht_item* create_item(char*key, char*value);
Hash_table* create_table(int size);
void free_item(Ht_item* item);
void free_table(Hash_table*table);
void insert_item(Hash_table*table,char*key,char*value);
void collision(List**head,Ht_item*item);
Ht_item *find_item(Hash_table*table,char*key);
void printf_table(Hash_table*table);
void print_item(Hash_table*table);
void add_str(Hash_table *table);
void upload(FILE*database,Hash_table *table,int N);
char*generate_ip();
void delete_item(Hash_table*table);

int check_int(){
    char ch;
    while((ch=(char)getchar())!='\n'){
        if(ch<'0'|| ch>'9'){
            fflush(stdin);
            return -1;
        }
    }
    return 1;
}

void check_from_1_to_6(int *choose){
    int rc,sc;
    do{
        rc=scanf_s("%d",choose);
        sc=check_int();
        if(*choose<1 || *choose>6)
            rc=-1;
        if(rc!=1 || sc==-1)
            printf("Incorrect input.\n");
    }while(rc!=1 || sc==-1);
}

void upload(FILE*database,Hash_table *table,int N){
    if(database==NULL){
        printf("ERROR!\n");
        return;
    }
    char*key,*value;
    for(int k=0;k<N;k++) {
        int n=1,i=0;
        key=(char*)calloc(n,sizeof(char));
        value=(char*)calloc(n,sizeof(char));
        char c='\'';
        while(c!=' '){
            if(c!='\'') {
                key[i] = c;
                n++;
                key = (char *) realloc(key, n * sizeof(char));
                i++;
           }
            c=(char)fgetc(database);
        }
        key[i]='\0';
        c=(char)fgetc(database);
        i=0;
        n=1;
        while(c!='\n' ){
            value[i]=c;
            n++;
            value=(char*)realloc(value,n*sizeof(char));
            i++;
            c=(char)fgetc(database);
        }
        value[i]='\0';
        insert_item(table,key,value);
    }

}

void add_str(Hash_table *table){
    char*key,*value;
    key=(char*)calloc(1,sizeof(char));
    value=(char*)calloc(1,sizeof(char));

   printf("Input a key:\n");
   char buf[254];
   fgets(buf,254,stdin);
   size_t len=strlen(buf);
   buf[len-1]='\0';


    strcpy(key,buf);
    printf("Input a value:\n");
    fgets(buf,254,stdin);
    len=strlen(buf);
    buf[len-1]='\0';
    strcpy(value,buf);
        insert_item(table,key,value);


}

size_t hash_function(const char* str)
{
    size_t h_code=0;
    for (int i=0;i<strlen(str);i++)
        h_code=(h_code*171+(size_t)str[i]);
    return h_code % CAPACITY;
}

Ht_item* create_item(char*key, char*value)
{
    Ht_item *item=(Ht_item*)calloc(1,sizeof(Ht_item));
    item->key=(char*)calloc(strlen(key)+1,sizeof(char));
    item->value=(char*)calloc(strlen(value)+1,sizeof(char));
    item->ip=(char*)calloc(22,sizeof(char));
    strcpy(item->ip,generate_ip());
    strcpy(item->key,key);
    strcpy(item->value,value);

    return item;
}

Hash_table* create_table(int size){
    Hash_table * table=(Hash_table*)calloc(1,sizeof(Hash_table));
    table->size=size;
    table->count=0;
    table->items=(Ht_item**)calloc(table->size,sizeof(Ht_item*));
    table->lists=(List**)calloc(table->size,sizeof(List*));
    for(int i=0;i<table->size;i++) {
        table->items[i] = NULL;
        table->lists[i] = NULL;
    }
    return table;
}

void free_item(Ht_item* item){
    free(item->ip);
    free(item->value);
    free(item->key);
    free(item);
}

void free_table(Hash_table*table){
    Ht_item *p;
    List*l;
    for(int i=0;i<table->size;i++) {
        p = table->items[i];
        l=table->lists[i];
        if(p!=NULL)
            free(p);
        if(l!=NULL)
            free(l);
    }
    free(table->items);
    free(table->lists);
    free(table);
}

void insert_item(Hash_table*table,char*key,char*value){

    Ht_item *item= create_item(key,value);
    size_t index=hash_function(key);


    if(table->items[index]==NULL){
        if(table->count ==table->size){
            printf("Hash table is full.\n");
            free_item(item);
            return;
        }
        table->items[index]=item;

        List*head=(List*)calloc(1,sizeof(List));
        head->prev=NULL;
        head->next=NULL;
        head->item=item;
        table->lists[index]=head;
        table->count++;
        return;
    }
    else{
       table->count++;
        if(strcmp(table->items[index]->key,key)==0) {
            strcpy(table->items[index]->value, value);
            return;
        }
        else{
            collision(&table->lists[index],item);
            return;
        }

    }
}

void collision(List**head,Ht_item*item){
    List*temp=(List*)calloc(1,sizeof(List));
    temp->item=item;
    temp->next=NULL;
    temp->prev=NULL;
    List*p=*head;
    List*tail;
    while(p!=NULL){
        tail=p;
        p=p->next;
    }
    p=*head;
    while(p!=NULL){
        if(strcmp(item->key,p->item->key)<0){
            if(p!=*head)
                p->prev->next=temp;
            temp->prev=p->prev;
            temp->next=p;
            p->prev=temp;
            if(p==*head)
                *head=temp;
            return;
        }
        else
            p=p->next;
    }
    tail->next=temp;
    temp->prev=tail;
}

Ht_item * find_item(Hash_table*table,char*key){
     size_t index= hash_function(key);
    if(table->items[index]!=NULL) {
        List *p;
        p = table->lists[index];
        while (p != NULL) {
            if (strcmp(table->items[index]->key, key) == 0)
                return p->item;
            p=p->next;
        }
    }
    return NULL;
}

void printf_table(Hash_table*table){
    if(table->count==0){
        printf("Table is empty.\n");
        return;
    }
    printf("\nHash Table\n-----------------------\n");
    for(int i=0;i<table->size;i++) {
        if (table->items[i] != NULL) {
           /* printf("Index: %d, Key: %s, Value : %s, Ip: %s\n", i, table->items[i]->key, table->items[i]->value, table->items[i]->ip);*/
            List*p=table->lists[i];
            while(p!=NULL) {
                printf("Index: %d, Key: %s, Value : %s, Ip: %s\n", i, p->item->key, p->item->value,p->item->ip);
                p=p->next;
            }
        }
    }

    printf("----------------------\n\n");
}

void print_item(Hash_table*table){
    if(table->count==0){
        printf("Table is empty.\n");
        return;
    }
    printf("Input a key to check:\n");
    char buf[255];
    fgets(buf,254,stdin);
    size_t len=strlen(buf);
    buf[len-1]='\0';
    char*key=(char*)calloc(strlen(buf)+1,sizeof(char));
    strcpy(key,buf);
    Ht_item *p;
    p= find_item(table,key);
    if(p!=NULL){
        printf("Ip of %s: %s",p->key,p->ip);
    }
    else
        printf("Key: %s doesn't exist.\n",key);
}

char*generate_ip(){
    int n=1;
    char*ip=(char*)calloc(n,sizeof(char));
    int IP[5];
    for(int i=0;i<4;i++) {
        IP[i] = rand() % 256;
    }
    IP[4]=rand()%65356;
    char buf[255];
    int k=0;
   for(int i=0;i<5;i++) {
       itoa(IP[i], buf, 10);
       int j = 0;
       while (buf[j] != '\0') {
           ip[k] = buf[j];
           n++;
           ip = (char *) realloc(ip, n * sizeof(char));
           j++;
           k++;
       }
       if (i < 3) {
           ip[k] = '.';
           k++;
           n++;
           ip = (char *) realloc(ip, n * sizeof(char));
       }
       if (i == 3) {
           ip[k] = ':';
           k++;
           n++;
           ip = (char *) realloc(ip, n * sizeof(char));
       }
   }
   ip[k]='\0';
   return ip;
}

void delete_item(Hash_table*table){
    if(table->count==0){
        printf("Table is empty.\n");
        return;
    }
    char* key=(char*)calloc(1,sizeof(char));
    char buf[255];
    printf("Input a key to delete an item.\n");
    fgets(buf,254,stdin);
    size_t len=strlen(buf);
    buf[len-1]='\0';
    strcpy(key,buf);

    size_t index= hash_function(key);
    if(table->items[index]==NULL){
        printf("There is no such element.\n");
        return;
    }
    else{
        List*p,*head;
        p=table->lists[index];
        head=table->lists[index];
        while(p!=NULL){
            if(strcmp(key,p->item->key)==0){
                if(p==head){
                    if(p->next!=NULL) {
                        head=p->next;
                        head->prev = NULL;
                        table->items[index] = head->item;
                        free_item(p->item);
                    }
                    table->items[index]=NULL;
                    free(table->lists[index]->item);
                }
                else{
                    p->prev->next=p->next;
                    if(p->next!=NULL)
                        p->next->prev=p->prev;
                    free(p->item);
                }
            }
            p=p->next;
        }
        printf("String was deleted.\n");
    }
}