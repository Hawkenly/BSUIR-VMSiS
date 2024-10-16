#include <iostream>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <unordered_map>
#include <string>
#include <ctime>
#define AMOUNT 701
using namespace std;


char*generate_ip();
int check_int();
void check_from_1_to_6(int *choose);
void upload(FILE*database,char**key,char**value);

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

void upload(FILE*database,char**key,char**value){
        int n=1,i=0;
        *key=(char*)calloc(n,sizeof(char));
        *value=(char*)calloc(n,sizeof(char));
        char c='\'';
        while(c!=' '){
            if(c!='\'') {
                (*key)[i] = c;
                n++;
                *key = (char *) realloc(*key, n * sizeof(char));
                i++;
            }
            c=(char)fgetc(database);
        }
    (*key)[i]='\0';
        c=(char)fgetc(database);
        i=0;
        n=1;
        while(c!='\n'){
            (*value)[i]=c;
            n++;
            *value=(char*)realloc(*value,n*sizeof(char));
            i++;
            c=(char)fgetc(database);
        }
    (*value)[i]='\0';

}

char*generate_ip(char**ip){
    int n=1;
    *ip=(char*)calloc(n,sizeof(char));
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
            (*ip)[k] = buf[j];
            n++;
            *ip = (char *) realloc(*ip, n * sizeof(char));
            j++;
            k++;
        }
        if (i < 3) {
            (*ip)[k] = '.';
            k++;
            n++;
            *ip = (char *) realloc(*ip, n * sizeof(char));
        }
        if (i == 3) {
            (*ip)[k] = ':';
            k++;
            n++;
            *ip = (char *) realloc(*ip, n * sizeof(char));
        }
    }
    (*ip)[k]='\0';
    return *ip;
}

