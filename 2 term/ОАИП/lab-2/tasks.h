#include "functions.h"
void task1(char*name){
    printf("\nTask 1: Fill in the file with words from the keyboard. Print the contents of the file to the screen.\n");
    char c;
    input_words(name);
    FILE*in;
    in=fopen(name,"rt");
    if(in==NULL){
        printf("\nThis file was deleted\n");
        _getch();
        exit(1);
    }
    c=(char)fgetc(in);
    while(!feof(in)){
        putchar(c);
        c=(char)fgetc(in);
    }
    fclose(in);
    _getch();
}

void task2(char*name){
    printf("\nTask 2: Find words in the file whose length is equal to the number entered from the keyboard.\n");
    FILE*out;
    out=fopen(name,"rt");
    if(out==NULL){
        printf("\nThis file was deleted\n");
        _getch();
        exit(1);
    }
    printf("\nInput the amount of letters word should contain\n");
    int amount;
    check(&amount);
    fflush(stdin);
    char*str;
    str=(char*)calloc(1,1);
    if(fgets(str,255,out)==NULL){
        printf("\nThe file is empty.\n");
        exit(1);
    }
    rewind(out);
    printf("\nWord(s) that contain(s) %d letters:\n",amount);
    while(fgets(str,255,out)!=NULL){
        int length;
        length=strlen(str);
        if(length==amount){
            printf("%s",str);
        }
    }
    fclose(out);
    _getch();
}

void task3(char*name){
    printf("\nTask 3: Make a reverse of all words with a length greater than the given one.\n");
    FILE*out;
    out=fopen(name,"r+t");
    if(out==NULL){
        printf("\nThis file was deleted\n");
        exit(1);
    }
    printf("\nInput the length of the word.\n");
    int amount;
    check(&amount);
    while(amount==0){
        printf("\nThe length of the word not be able to be 0, so reinput.\n ");
        check(&amount);
    }
    reverse(out,amount);
    fclose(out);
    out=fopen(name,"rt");
    if(out==NULL){
        printf("\nThis file was deleted.\n");
        exit(1);
    }
    char c;
    c=(char)fgetc(out);
    while(!feof(out)){
        printf("%c",c);
        c=(char)fgetc(out);
    }
    fclose(out);
}