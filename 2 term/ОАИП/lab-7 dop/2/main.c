#include "functions.h"

int main() {
    SetConsoleCP (1251);
    SetConsoleOutputCP (1251);
    setlocale(0,"");

    FILE*file;
    file=fopen("Dictionary.txt","rt+");
    if(file==NULL){
        printf("Error!\n");
        _getch();
        return 0;
    }
    char*eng,*rus;
    int len=0;
    eng=(char*)calloc(1,sizeof(char));
    rus=(char*)calloc(1,sizeof(char));
    char c,h;

    node*root=NULL;

    do{
       do{
           h=(char)fgetc(file);
       }while(if_letter(h)==0);
       int i=0;
       do{
           eng=(char*)realloc(eng,(len+1)*sizeof(char));
           eng[i]=h;
           len++;
           i++;
           h=(char)fgetc(file);
       }while(h!='=' && h!=EOF);

       if(h=='=');
       else
           break;
       int j=0;
       len=0;
       h=(char)fgetc(file);

       while((h!=';'||(rus[j]!=' ' && rus[j-1]!=' ') )&& h!=EOF ) {
           if(h=='='){
               printf("Incorrect file\n");
               return 0;
           }
           rus = (char *) realloc(rus, (len + 1) * sizeof(char));
           rus[j] = h;
           len++;
           j++;
           h=(char)fgetc(file);
       }
       eng[i]='\0';
       rus[j]='\0';
        create_dict(&root,eng,rus);
    }while(h!=EOF);



    print_dict(root);

    _getch();


    return 0;
}
