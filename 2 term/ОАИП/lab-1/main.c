
#include "task1.h"

int main(int argc, char**argv) {
    if(argc!=2){
        printf("\nThis program should be launched like this:"
               "\nlab_1.exe name.bin");
       fflush(stdin);
        exit(1);
    }
    char*name=argv[1];

   task1(name);
   task2(name);
   task3(name);
   task4(name);
    return 0;
}
