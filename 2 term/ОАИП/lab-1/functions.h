#include  <stdio.h>
#include <stdlib.h>
#include<conio.h>



//FOR TASK 1
void input_bin(FILE *in){
    printf("\nInput different integer nums in file, to stop entering input anything else.\nIf u combined nums and letters in file will be printed first numbers\n");
    int c;
    while(1){
        if(scanf_s("%d",&c)!=1)
            break;
        if(c-(int)c!=0)
            break;
        fwrite(&c, sizeof(int),1,in);
        fflush(stdin);
    }
    fclose(in);
    fflush(stdin);
    printf("\n");
}
void output_bin(const char*name){
    FILE*out;
    out=fopen(name,"rb");
    if(out==NULL){
        printf("\nFile was deleted.\n");
        _getch();
        fclose(out);
        exit(1);
    }
    int h;
    printf("\n");
    while(1){
        if (fread(&h, sizeof(int), 1, out) != 1)
            break;
        printf("%d\n", h);
    }
    fclose(out);
}
//FOR TASK 2
void find_max(int*max,FILE*f){
    int c;
   if(fread(max,sizeof(int),1,f)==0){
       printf("\nThe file is empty.\n");
       _getch();
       fclose(f);
       exit(1);
   }
    while(fread(&c,sizeof(int),1,f)==1){
        if(c>*max){
            *max=c;
        }
    }
}
void count_max(int max,int*count,FILE*f){
    int c;
    while(fread(&c,sizeof(int),1,f)==1){
        if(c==max)
            (*count)++;
    }
}
//FOR TASK 3
void find_min(int*min,FILE*f){
    int c;
    if(fread(min,sizeof(int),1,f)==0){
        printf("\nThe file is empty.\n");
        _getch();
        fclose(f);
        exit(1);
    }
    while(fread(&c,sizeof(int),1,f)==1){
        if(c<*min){
            *min=c;
        }
    }
}
//FOR TASK 4
void find_min_pos(int*min,fpos_t *min_pos,FILE*f){
    int c;
    while(fread(&c,sizeof(int),1,f)==1){
        if(c>0 && c<*min){
            *min=c;
            fseek(f,(-1)*(int)sizeof(int),SEEK_CUR);
            fgetpos(f,min_pos);
        }
    }
}
void output(FILE*f){
    rewind(f);
    int h;
    printf("\n");
    while(fread(&h,sizeof(int),1,f)==1) {
        printf("%d\n", h);
    }
    fclose(f);
}

void sort_positive(FILE*f,int count){
    while(count>0){
        int buf;
        fpos_t pos;
        fgetpos(f,&pos);
        fread(&buf,sizeof(int),1,f);
        fseek(f,(-1)*(int)sizeof(int),SEEK_CUR);
        if(buf>=0){
            int min=buf;
            fpos_t min_pos;
            find_min_pos(&min,&min_pos,f);
            fsetpos(f,&pos);
            fwrite(&min,sizeof(int),1,f);
            fsetpos(f,&min_pos);
            fwrite(&buf,sizeof(int),1,f);
        }
        fsetpos(f,&pos);
        fseek(f,sizeof(int),SEEK_CUR);
        count--;
    }

}