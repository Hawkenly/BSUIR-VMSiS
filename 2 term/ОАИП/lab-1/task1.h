#include "functions.h"

void task1(char*name) {
    printf("\nTask1:\nFill the file with the integers by the keyboard.\n");
    FILE*in;
    in=fopen(name,"wb");
    input_bin(in);

    output_bin(name);
    _getch();
    printf("\n");

}

void task2(char*name){
printf("Task2:\nCount how many elements with max value are in file.\n");
  FILE*out;
    out=fopen(name,"rb");
    if(out==NULL){
        printf("\nThis file doesn't exist\n");
        _getch();
       exit(1);
    }
  int max;
  find_max(&max,out);
  rewind(out);
    int count=0;
    count_max(max,&count,out);
    fclose(out);
    printf("\nThere are %d element(s) with max value.\n",count);
   _getch();
   printf("\n");

}

void task3(char*name){
    printf("Task3:\nReplace all maximum elements with the value of the minimum element.\n");
    FILE*out;
    out=fopen(name,"r+b");
    if(out==NULL){
        printf("\nFile doesn't exist\n");
        _getch();
        exit(1);
    }
    int min,max;
    find_min(&min,out);
    rewind(out);
   find_max(&max, out);
   rewind(out);
   int count=0;
    count_max(max,&count,out);
    rewind(out);
    int l=0;
    while(count>0) {
        fread(&l, sizeof(int), 1, out);
        if (l == max) {
            fseek(out, -4, SEEK_CUR);
            fwrite(&min, sizeof(int), 1, out);
            count--;
        }
    }
    output(out);
    _getch();
    printf("\n");
}
void task4(char*name){
    printf("Task4:\nSort positive numbers in a file.\n");
    FILE*out=fopen(name,"rb+");
    if(out==NULL){
        printf("\nThis file was deleted.\n");
        _getch();
       exit(1);
    }
    int count=0;
    int c;
    while(fread(&c,sizeof(int),1,out)==1){
        count++;
    }
    if(count==0){
        printf("\nFile was changed.\n");
        _getch();
       exit(1);
    }
    rewind(out);
    sort_positive(out,count);
    output(out);
    _getch();
    printf("\n");
}
