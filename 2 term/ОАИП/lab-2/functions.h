#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void check(int*choose) {
    int rc;
    while(1) {
        rc=scanf_s("%d",choose);
        if(rc==0){
            printf("\nThis is not a positive integer number.Try again.\n");
            fflush(stdin);
            continue;
        }
        char ch;
        int fl=0;
        while ((ch = (char)getchar()) != '\n') {
            if (ch <'0' || ch>'9'){
                printf("\nThis is not a positive integer number.Try again.\n");
                fflush(stdin);
                fl=1;
                break;
            }
        }
        if(fl==1)
            continue;
        break;
    }
}

void input_words(char*name){
    FILE*out;
    out=fopen(name,"wt");
    printf("\nInput a word. Word is the continuous sequence of letters.\nIf there is no letter everything after it will be deleted.\n");
    char*text;
    text=(char*)calloc(1,1);
    scanf_s("%s",text);
    char*buf;
    buf= strtok(text," ");
   while(buf!=NULL) {
       fprintf(out, "%s", buf);
       buf = strtok(NULL, " ");
   }
   /* while(1) {
        printf("Your word: \n");
        char *str;
        int n = 1;
        char ch;
        str = (char *) calloc(n, sizeof(char));
        int i = 0;
        while ((ch = (char) getchar()) != EOF && ch!='\n'  ) {
            if ((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')) {
                str[i] = ch;
                i++;
                n++;
                str = (char *) realloc(str, n * sizeof(char));
            }
            else
                break;
            }
        str[i] = '\0';
        fputs(str, out);
        fputc('\n',out);
        fflush(stdin);
        printf("\nIf this is your last word press 1,else input another [positive integer] number\n");*/
       /* int choose ;
        check(&choose);
        if(choose==1){
                break;
        }*/
        fflush(stdin);

fclose(out);
}


void reverse(FILE*f,int amount){
    char*buf;
    buf=(char*)calloc(1,1);
    while(fgets(buf,255,f)!=NULL){
        int length;
        length=strlen(buf)-1;
        if(length>amount){
            char c1,c2;
            fpos_t start_next;
            fgetpos(f,&start_next);

            int l=length;
            fseek(f,(-3)*sizeof(char),SEEK_CUR);
            fpos_t pos2;
            fgetpos(f,&pos2);

            fseek(f,-(l-1)*sizeof(char),SEEK_CUR);
            fpos_t pos1;
            fgetpos(f,&pos1);
            while(length>1){
                fsetpos(f,&pos1);
                c1=(char)fgetc(f);


                fsetpos(f,&pos2);
                c2=(char)fgetc(f);

                fsetpos(f,&pos1);
                fputc(c2,f);
                fgetpos(f,&pos1);

                fsetpos(f,&pos2);
                fputc(c1,f);
                fseek(f,(-2)*sizeof(char),SEEK_CUR);
                fgetpos(f,&pos2);

                length-=2;
            }
        }
    }
}