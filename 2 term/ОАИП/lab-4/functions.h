#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

union remainder{
    unsigned int num;
    unsigned int bit2 :1;
    unsigned int bit4 :2;
    unsigned int bit8 :3;
    unsigned int bit16 :4;
    unsigned int bit32 :5;
    unsigned int bit64 :6;
    unsigned int bit128 :7;
};


typedef struct Events{
    int id;
    char*date;
    char*name;
    struct {
        char * info;
        struct{
            struct {
                char*fsrt;
                char*scnd;
            }short_info;
            struct{
                char*location;
                char*time;
            }one;
            struct{
                char* holiday_name;
                char* members;
            }two;
            struct{
                char* brief_remainder;
                char*task_name;
            }three;
        }short_info;
    }info;
    struct Events *next;
}Events;

Events * init();
void add_elem(Events **event,int i);
int check_int();
void check_1_or_2(int*choose);
void check_date(char*date,int fl,Events*event);
void check_1_2_3_4_5_6(int*choose);
void check_1_2_3_4(int*choose);
void check_1_2_3(int*choose);
void add_field(char*buf,char**field);
void add_part(Events*event, int i);
void delete_elem( Events** root);
void output_one(Events**event);
int find_event_default(Events**root);
void find_event_new(Events**root);
void find_new_part(Events*temp,int*count,char*str1, char*str2,char*def_str1,char*def_str2,int*id, int*i);
int check_id(Events*root,const int *id,int n);
void date_numbers(const char *date, int *d, int *mo, int *ye) ;
int amount_events(Events*root);
void swap(Events *event1, Events *event2, Events **root);
void sort_new(Events**root);
void sort_default(Events**root);
void output_list(Events** root);
void ptr_pos(Events*p1, Events*p2,Events*root,int*i1, int*i2);
Events* longest_name(Events*root);
Events* longest_info(Events*root);
int longest_short_info(Events*root);
void log_(const char*format,  ...);


// Инициализация списка (ОЛС)
Events * init()
{

    Events *event;
    // выделение памяти под корень списка
    event = (Events*)malloc(sizeof(Events));

    add_part(event,0);


    event->next = NULL; // это последний узел списка
    return(event);
}

void add_part(Events*event,int i){
    int choose;
    event->id = i+1;
    printf("The %d event:\n",event->id);
    printf("//////////////////////////////////\n");
    char buf[255];

    check_date(buf,1,event);
    event->date = (char *) calloc(strlen(buf) + 1, sizeof(char));
    strcpy(event->date, buf);

    printf("Name: ");
    add_field(buf,&event->name);

    printf("Info: ");
    add_field(buf,&event->info.info);

    event->info.short_info.short_info.fsrt=NULL;
    event->info.short_info.short_info.scnd=NULL;
    event->info.short_info.one.location = NULL;
    event->info.short_info.one.time=NULL;
    event->info.short_info.two.holiday_name = NULL;
    event->info.short_info.two.members=NULL;
    event->info.short_info.three.brief_remainder = NULL;
    event->info.short_info.three.task_name=NULL;


    printf("------------------------\n");
    printf("Choose short info field:\n1 - Location and time\n2 - Holiday name and members\n3 - Task name and brief remainder\n4 - Nothing\n");
    check_1_2_3_4(&choose);
    if (choose == 1) {
        if (event->info.short_info.one.location == NULL) {
            printf("------------------------\n");
            printf("Input location:\n");
            add_field(buf, &event->info.short_info.one.location);
            event->info.short_info.short_info.fsrt=event->info.short_info.one.location;


            printf("Input time:\n");
            add_field(buf, &event->info.short_info.one.time);
            event->info.short_info.short_info.scnd=event->info.short_info.one.time;



        }
        else {
            printf("------------------------\n");
            printf("There already have been information\n");
        }
    }
    if (choose == 2) {
        if (event->info.short_info.two.holiday_name == NULL) {
            printf("------------------------\n");
            printf("Input holiday name:\n");
            add_field(buf, &event->info.short_info.two.holiday_name);
            event->info.short_info.short_info.fsrt=event->info.short_info.two.holiday_name;


            printf("Input members:\n");
            add_field(buf, &event->info.short_info.two.members);
            event->info.short_info.short_info.scnd=event->info.short_info.two.members;


        }
        else {
            printf("------------------------\n");
            printf("There already have been information\n");
        }
    }
    if (choose == 3) {
        if (event->info.short_info.three.task_name == NULL) {
            printf("------------------------\n");
            printf("Input task name:\n");
            add_field(buf, &event->info.short_info.three.task_name);
            event->info.short_info.short_info.fsrt=event->info.short_info.three.task_name;


            printf("Input a brief remainder:\n");
            add_field(buf, &event->info.short_info.three.brief_remainder);\
            event->info.short_info.short_info.scnd=event->info.short_info.three.brief_remainder;

        }
        else{
            printf("------------------------\n");
            printf("There already have been information\n");
        }
    }

}

// Добавление элемента (возвращает добавленный элемент) (ОЛС)
void add_elem(Events **event,int i) //указатель на предыдущий элемент
{
    Events *temp, *p;
    temp = (Events*)malloc(sizeof(Events));

    p = (*event)->next; // сохранение указателя на следующий узел
    (*event)->next = temp; // предыдущий узел указывает на создаваемый

    // сохранение поля данных добавляемого узла
    add_part(temp,i);

    temp->next = p; // созданный узел указывает на следующий элемент (т.е на NULL)
}
void add_field(char*buf,char**field){
    size_t len;
    fgets(buf, 253, stdin);
    fflush(stdin);
    len = strlen(buf);
    buf[len - 1] = '\0';
    * field = (char *) calloc(strlen(buf) + 1, sizeof(char));
    strcpy(*field, buf);
}


int check_int(){
    char ch;
    while((ch=(char)getchar())!='\n'){
        if(ch<'0'|| ch>'9'){
            log_("Input error.");
            printf("Wrong input\n");
            fflush(stdin);
            return -1;
        }
    }
    return 1;
}
void check_1_or_2(int*choose) {
    int sr ;
    do {
        scanf_s("%d", choose);
        sr = check_int();
        if (sr == 1) {
            if (*choose < 1 || *choose > 2) {
                log_("Input error.");
                printf("Wrong input\n");
                sr = -1;
                fflush(stdin);
            }
        }
    } while (sr == -1);
    fflush(stdin);
}
void check_1_2_3_4(int*choose){
    int sr ;
    do {
        scanf_s("%d", choose);
        sr = check_int();
        if (sr == 1) {
            if (*choose < 1 || *choose > 4) {
                log_("Input error.");
                printf("Wrong input\n");
                sr = -1;
                fflush(stdin);
            }
        }
    } while (sr == -1);
    fflush(stdin);
}
void check_1_2_3_4_5_6(int*choose){
    int sr ;
    do {
        scanf_s("%d", choose);
        sr = check_int();
        if (sr == 1) {
            if (*choose < 1 || *choose > 6) {
                log_("Input error.");
                printf("Wrong input\n");
                sr = -1;
                fflush(stdin);
            }
        }
    } while (sr == -1);
    fflush(stdin);
}
void check_1_2_3(int*choose){
    int sr ;
    do {
        scanf_s("%d", choose);
        sr = check_int();
        if (sr == 1) {
            if (*choose < 1 || *choose > 3) {
                log_("Input error.");
                printf("Wrong input\n");
                sr = -1;
                fflush(stdin);
            }
        }
    } while (sr == -1);
    fflush(stdin);
}
void check_date(char*date,int fl,Events*event){
    fflush(stdin);
    if (fl == 1)
        printf("Date [ _ _ . _ _ . _ _ _ _ ]: ");
    fgets(date, 254, stdin);
    // fflush(stdin);
    size_t len = strlen(date);

    date[len-1]='\0';
    len=strlen(date);
    if (len != 10) {
        printf("Wrong format, input like this [ _ _ . _ _ . _ _ _ _ ]\n");
        log_("Input error.");
        check_date(date, fl,event);
    }
    int i = 0;
    while (date[i] != '\0') {
        if ((date[i] >= '0' && date[i] <= '9') || date[i] == '.')
            i++;
        else {
            printf("Date should consist of numbers and dotes\n");
            log_("Input error.");
            check_date(date, fl,event);
        }
    }
    int j = 0;
    char day[3], month[3], year[5];
    while (date[j] != '.') {
        if (j == 2) {
            printf("Wrong format, input like this [ _ _ . _ _ . _ _ _ _ ]\n");
            log_("Input error.");
            check_date(date, fl,event);
        }
        day[j] = date[j];
        j++;
    }
    day[j] = '\0';
    j++;
    while (date[j] != '.') {
        month[j - 3] = date[j];
        j++;
    }
    month[j - 3] = '\0';
    j++;
    while (date[j] != '\0') {
        year[j - 6] = date[j];
        j++;
    }
    year[j - 6] = '\0';
    int day_, month_, year_;
    day_ = atoi(day);
    if (day_ < 1 || day_ > 31) {
        printf("Wrong day\n");
        log_("Input error.");
        check_date(date, fl,event);
    }
    month_ = atoi(month);
    if (month_ < 1 || month_ > 12) {
        printf("Wrong month\n");
        log_("Input error.");
        check_date(date, fl,event);
    }
    year_ = atoi(year);
    if (year_ < 1 || year_ > 3000) {
        printf("Wrong year\n");
        log_("Input error.");
        check_date(date, fl,event);
    }
    if(month_==2 && year_%4==0 && day_>29){
        printf("Wrong day\n");
        log_("Input error.");
        check_date(date, fl,event);
    }
    if(month_==2 && year_%4!=0 && day_>28){
        printf("Wrong day\n");
        log_("Input error.");
        check_date(date, fl,event);
    }
}



void delete_elem(Events** root)
{
    int id;
   id= find_event_default(root);
    if(id==-1){
        printf("There are no coincidences.");
        log_("Not available to delete.");
        return;
    }

    printf("------------------------\n");

    Events* temp,*event,*p;
    temp= *root;
    p=*root;
    if(id==1){
        temp=(*root)->next;
        *root=NULL;
        *root=temp;
        p=*root;
        int i=1;
        while(p!=NULL){
            p->id=i;
            p=p->next;
            i++;
        }
    }
    if(id>1) {
        while (id > 1) {
            p = p->next;
            id--;
        }
        event = p;
        while (temp->next != event)        // просматриваем список начиная с корня
        {        // пока не найдем узел, предшествующий удаляемому
            temp = temp->next;
        }
        temp->next = event->next; // переставляем указатель
        log_("The %d event '%s' was successfully deleted.",event->id,event->name);
        free(event);    // освобождаем память удаляемого элемента
    }
    if(*root!=NULL) {
        output_list(root);
    }

}

int find_event_default(Events**root){
    int n= amount_events(*root);
    int id[n];
    int i=0;
    char*name=NULL;
    printf("Input a name of the event:\n");
    char buf[255];
    fgets(buf,253,stdin);
    fflush(stdin);
    size_t len;
    len=strlen(buf);
    buf[len-1]='\0';
    name=(char*)calloc(strlen(buf)+1,sizeof(char));
    strcpy(name,buf);
    Events*temp;
    temp=*root;
    int count=0;
    while(temp!=NULL){
        char*ptr=NULL;
        ptr=strstr(temp->name,name);//возвращает указатель на начало совпадения строк
        if(ptr-(temp->name)+1==1){
            id[i]=temp->id;
            i++;
            count++;
            output_one(&temp);
        }
        temp=temp->next;
    }
    if(count==0){
        printf("------------------------\n");
        printf("There are no coincidences\n");
        printf("------------------------\n");
    }
   int id_= check_id(*root,id,count);
    return id_;
}
void find_event_new(Events**root){
    int n= amount_events(*root);
    int*id;
    id=(int*)malloc(sizeof(int)*n);
    int count=0;
    int i=0;
    int choose;
    char*str1=NULL;
    char*str2=NULL;
    char buf[255];
    printf("Choose a new field to find:\n1 - Location and time\n2 - Holiday name and members\n3 - Task name and brief remainder\n");
    check_1_2_3(&choose);
    if(choose==1){
        printf("Input location:\n");
        fgets(buf,253,stdin);
        fflush(stdin);
        size_t len;
        len=strlen(buf);
        buf[len-1]='\0';
        str1=(char*)calloc(strlen(buf)+1,sizeof(char));
        strcpy(str1,buf);

        printf("Input time:\n");
        fgets(buf,253,stdin);
        fflush(stdin);
        len=strlen(buf);
        buf[len-1]='\0';
        str2=(char*)calloc(strlen(buf)+1,sizeof(char));
        strcpy(str2,buf);

        Events*temp;
        temp=*root;
        while(temp!=NULL){
            find_new_part(temp,&count,str1,str2,temp->info.short_info.one.location,temp->info.short_info.one.location,id,&i);
            temp=temp->next;
        }
        if(count==0){
            printf("------------------------\n");
            printf("There are no coincidences\n");
            printf("------------------------\n");
        }

    }
    if(choose==2){
        printf("Input holiday name:\n");
        fgets(buf,253,stdin);
        fflush(stdin);
        size_t len;
        len=strlen(buf);
        buf[len-1]='\0';
        str1=(char*)calloc(strlen(buf)+1,sizeof(char));
        strcpy(str1,buf);

        printf("Input members:\n");
        fgets(buf,253,stdin);
        fflush(stdin);
        len=strlen(buf);
        buf[len-1]='\0';
        str2=(char*)calloc(strlen(buf)+1,sizeof(char));
        strcpy(str2,buf);

        Events*temp;
        temp=*root;
        while(temp!=NULL){
            find_new_part(temp,&count,str1,str2,temp->info.short_info.two.holiday_name,temp->info.short_info.two.members,id,&i);
            temp=temp->next;
        }
        if(count==0){
            printf("------------------------\n");
            printf("There are no coincidences.\n");
            printf("------------------------\n");
        }

    }
    if(choose==3){
        printf("Input task name:\n");
        fgets(buf,253,stdin);
        fflush(stdin);
        size_t len;
        len=strlen(buf);
        buf[len-1]='\0';
        str1=(char*)calloc(strlen(buf)+1,sizeof(char));
        strcpy(str1,buf);

        printf("Input brief remainder:\n");
        fgets(buf,253,stdin);
        fflush(stdin);
        len=strlen(buf);
        buf[len-1]='\0';
        str2=(char*)calloc(strlen(buf)+1,sizeof(char));
        strcpy(str2,buf);
        Events*temp;
        temp=*root;
        while(temp!=NULL){
            find_new_part(temp,&count,str1,str2,temp->info.short_info.three.task_name,temp->info.short_info.three.brief_remainder,id,&i);
            temp=temp->next;
        }
    }
    check_id(*root,id,count);
    if(count==0){
        printf("------------------------\n");
        printf("There are no coincidences.\n");
        printf("------------------------\n");
    }

}

void find_new_part(Events*temp,int*count,char*str1, char*str2,char*def_str1,char*def_str2,int*id,int *i){
        char*ptr=NULL;
        if(def_str1==NULL){
            return;
        }
        ptr=strstr(def_str1,str1);//возвращает указатель на начало совпадения строк
        if(ptr-(def_str1)+1==1) {
            (*count)++;
            id[*i] = temp->id;
            (*i)++;
            output_one(&temp);
        }
        else {
            ptr = strstr(def_str2, str2);
            if (ptr - (def_str2) + 1 == 1) {
                (*count)++;
                id[*i] = temp->id;
                (*i)++;
                output_one(&temp);
            }
            else
                return;
        }
}
int check_id(Events*root, const int *id,int n){
    printf("Input the id of needed event\n");
    int choose;
    scanf_s("%d",&choose);
    for(int i=0;i<n;i++){
        if(id[i]==choose){
            Events*temp;
            temp=root;
            while(temp!=NULL){
                if(temp->id==id[i]){
                    printf("Your event:\n");
                    output_one(&temp);
                    log_("The %d event '%s' was found.",temp->id,temp->name);
                    return temp->id;
                }
                temp=temp->next;
            }
        }
    }
    return -1;

}

void sort_new(Events**root) {
    int choose;
    int n = amount_events(*root);
    int fl;
    Events *p;
    printf("Choose a new field to sort:\n1 - Location and time\n2 - Holiday name and members\n3 - Brief remainder and task name\n");
    check_1_2_3(&choose);

    for (int gap = n / 2; gap > 0; gap /= 2) {
        do {
            p = *root;
            fl = 0;
            Events *p1 = p;
            int l = gap;
            while (l != 0) {
                p = p->next;
                l--;
            }
            Events *p2 = p;
            while (p1 != NULL && p2 != NULL) {
                int i1 = 0, i2 = 0;
                ptr_pos(p1, p2, *root, &i1, &i2);
                int dif = i2 - i1;
                if(choose==1){
                    if (dif>0 && ((p2->info.short_info.one.location!=NULL && p1->info.short_info.one.location==NULL )||  (p2->info.short_info.one.location!=NULL && p1->info.short_info.one.location!=NULL && strcmp(p1->info.short_info.one.location,p2->info.short_info.one.location)>=0))) {
                        if(p1->info.short_info.one.location==NULL || strcmp(p1->info.short_info.one.location,p2->info.short_info.one.location)>0 ) {
                            swap(p1, p2, root);
                            fl = 1;
                        }
                        else {
                            if (strcmp(p1->info.short_info.one.time, p2->info.short_info.one.time) > 0) {
                                swap(p1, p2, root);
                                fl = 1;
                            }
                        }
                    } else  if(dif<0 && ((p1->info.short_info.one.location!=NULL && p2->info.short_info.one.location==NULL)||  (p1->info.short_info.one.location!=NULL && p2->info.short_info.one.location!=NULL && strcmp(p2->info.short_info.one.location,p1->info.short_info.one.location)>=0) )) {
                        if(p2->info.short_info.one.location==NULL || strcmp(p2->info.short_info.one.location,p1->info.short_info.one.location)>0) {
                            swap(p2, p1, root);
                            fl = 1;
                        }
                        else {
                            if (strcmp(p2->info.short_info.one.time, p1->info.short_info.one.time) > 0) {
                                swap(p2, p1, root);
                                fl = 1;
                            }
                        }
                    }
                }
                if(choose==2){
                    if (dif>0 && ((p2->info.short_info.two.holiday_name!=NULL && p1->info.short_info.two.holiday_name==NULL )||  (p2->info.short_info.two.holiday_name!=NULL && p1->info.short_info.two.holiday_name!=NULL && strcmp(p1->info.short_info.two.holiday_name,p2->info.short_info.two.holiday_name)>=0))) {
                        if(p1->info.short_info.two.holiday_name==NULL || strcmp(p1->info.short_info.two.holiday_name,p2->info.short_info.two.holiday_name)>0) {
                            swap(p1, p2, root);
                            fl = 1;
                        }
                        else {
                            if (strcmp(p1->info.short_info.two.members, p2->info.short_info.two.members) > 0) {
                                swap(p1, p2, root);
                                fl = 1;
                            }
                        }
                    } else  if(dif<0 && ((p1->info.short_info.two.holiday_name!=NULL && p2->info.short_info.two.holiday_name==NULL)||  (p1->info.short_info.two.holiday_name!=NULL && p2->info.short_info.two.holiday_name!=NULL && strcmp(p2->info.short_info.two.holiday_name,p1->info.short_info.two.holiday_name)>=0) )) {
                        if(p2->info.short_info.two.holiday_name==NULL ||strcmp( p2->info.short_info.two.holiday_name,p1->info.short_info.two.holiday_name)>0) {
                            swap(p2, p1, root);
                            fl = 1;
                        }
                        else {
                            if (strcmp(p2->info.short_info.two.members, p1->info.short_info.two.members) > 0) {
                                swap(p2, p1, root);
                                fl = 1;
                            }
                        }
                    }
                }
                if(choose==3){
                    if (dif>0 && ((p2->info.short_info.three.brief_remainder!=NULL && p1->info.short_info.three.brief_remainder==NULL )||  (p2->info.short_info.three.brief_remainder!=NULL && p1->info.short_info.three.brief_remainder!=NULL && strcmp(p1->info.short_info.three.brief_remainder,p2->info.short_info.three.brief_remainder)>=0))) {
                        if(p1->info.short_info.three.brief_remainder==NULL || strcmp( p1->info.short_info.three.brief_remainder,p2->info.short_info.three.brief_remainder)>0) {
                            swap(p1, p2, root);
                            fl = 1;
                        }
                        else {
                            if (strcmp(p1->info.short_info.three.task_name, p2->info.short_info.three.task_name) > 0) {
                                swap(p1, p2, root);
                                fl = 1;
                            }
                        }
                    } else  if(dif<0 && ((p1->info.short_info.three.brief_remainder!=NULL && p2->info.short_info.three.brief_remainder==NULL)||  (p1->info.short_info.three.brief_remainder!=NULL && p2->info.short_info.three.brief_remainder!=NULL && strcmp(p2->info.short_info.short_info.fsrt,p1->info.short_info.short_info.fsrt)>=0) )) {
                        if(p2->info.short_info.three.brief_remainder==NULL || strcmp(p2->info.short_info.three.brief_remainder,p1->info.short_info.three.brief_remainder)>0) {
                            swap(p2, p1, root);
                            fl = 1;
                        }
                        else {
                            if (strcmp(p2->info.short_info.three.task_name, p1->info.short_info.three.task_name) > 0) {
                                swap(p2, p1, root);
                                fl = 1;
                            }
                        }
                    }
                }
                p1 = p1->next;
                p2 = p2->next;
            }

        } while (fl);
    }
}
void sort_default(Events**root) {
    int n= amount_events(*root);
    printf("Choose the field to sort:\n1 - Date\n2 - Name\n3 - Info\n");
    int choose;
    check_1_2_3(&choose);
    int fl;
    Events *p;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        do {
            p = *root;
            fl = 0;
            Events *p1 = p;
            int l = gap;
            while (l != 0) {
                p = p->next;
                l--;
            }
            Events *p2 = p;
            while (p1!=NULL && p2 != NULL) {
                int i1=0,i2=0;
                ptr_pos(p1,p2,*root,&i1,&i2);
                int dif=i2-i1;
                if (choose == 1) {
                    int d1, m1, y1;
                    int d2, m2, y2;
                    date_numbers(p1->date, &d1, &m1, &y1);
                    date_numbers(p2->date, &d2, &m2, &y2);
                    if (dif>0 && (y1 > y2 || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2))) {
                        swap(p1, p2, root);
                        fl = 1;
                    } else  if(dif<0 && (y1 < y2 || (y1 == y2 && m1 < m2) || (y1 == y2 && m1 == m2 && d1 < d2))) {
                        swap(p2, p1, root);
                        fl = 1;
                    }

                }
                if (choose == 2) {
                    if (dif>0 && strcmp(p1->name,p2->name)>0) {
                        swap(p1, p2, root);
                        fl = 1;
                    } else  if(dif<0 && strcmp(p2->name,p1->name)>0) {
                        swap(p2, p1, root);
                        fl = 1;
                    }

                }
                if (choose == 3) {
                    if (dif>0 && strcmp(p1->info.info,p2->info.info)>0) {
                        swap(p1, p2, root);
                        fl = 1;
                    } else  if(dif<0 && strcmp(p2->info.info,p1->info.info)>0) {
                        swap(p2, p1, root);
                        fl = 1;
                    }
                }
                p1=p1->next;
                p2 = p2->next;
            }

        } while (fl);

    }

}
void swap(Events *event1, Events *event2, Events **root)
{
    Events *prev1, *prev2, *next1, *next2;
    prev1 = *root;
    prev2 = *root;
    if (prev1 == event1)
        prev1 = NULL;
    else
        while (prev1->next != event1) // поиск узла предшествующего event1
            prev1 = prev1->next;
    if (prev2 == event2)
        prev2 = NULL;
    else
        while (prev2->next != event2) // поиск узла предшествующего event2
            prev2 = prev2->next;
    next1 = event1->next;  // узел следующий за event1
    next2 = event2->next;  // узел следующий за event2
    int fl=1;
    if (next1==event2)
    {
        // обмениваются соседние узлы
        if(event1 ==*root){
            *root=event2;
            fl=0;
        }
        if(fl==1) {
            prev1->next = event2;
        }
        event1->next = next2;
        event2->next = event1;
    }
    else
    {
        // обмениваются отстоящие узлы
        if(event1==*root){
            *root=event2;
            fl=0;
        }
        if(fl==1)
            prev1->next = event2;
        event1->next = next2;
        event2->next = next1;
        prev2->next = event1;
    }

}
void ptr_pos(Events*p1, Events*p2,Events*root,int*i1, int*i2){
    Events*temp;
    temp=root;
    while(temp!=NULL && temp!=p1){
        (*i1)++;
        temp=temp->next;
    }
    temp=root;
    while(temp!=NULL && temp!=p2){
        (*i2)++;
        temp=temp->next;
    }
}
void date_numbers(const char *date, int *d, int *mo, int *ye) {
    int j = 0;
    char day[3], month[3], year[5];
    while (date[j] != '.') {
        day[j] = date[j];
        j++;
    }
    day[j] = '\0';
    j++;
    while (date[j] != '.') {
        month[j - 3] = date[j];
        j++;
    }
    month[j - 3] = '\0';
    j++;
    while (date[j] != '\0') {
        year[j - 6] = date[j];
        j++;
    }
    year[j - 6] = '\0';


    *d= atoi(day);
    *mo= atoi(month);
    *ye = atoi(year);



}




void output_list(Events** root){
    Events*l_name=NULL,*l_info=NULL;
    l_name=longest_name(*root);
    l_info= longest_info(*root);
    int l_short_info= longest_short_info(*root);
    int l_namel=(int)strlen(l_name->name);
    int l_infol=(int)strlen(l_info->info.info);
    if(l_namel<4)
        l_namel=4;
    if(l_infol<4)
        l_infol=4;
    if(l_short_info<7)
        l_short_info=7;
    printf("| Id | Name%-*c | Date%-*c | Info%-*c | Short Info%-*c|\n",l_namel-4,' ',(int)(strlen((*root)->date)-4),' ',l_infol-4,' ',l_short_info-10+3,' ');
    Events*temp;
    temp=*root;
    printf("----------------------------------------------------------------------------------------------\n");
    while(temp!=NULL){
        if(l_namel==4)
            l_namel=5;
        if(l_infol==4)
            l_infol=5;
        printf("| %d  | %-*s | %s | %-*s |",temp->id, l_namel, temp->name,  temp->date, l_infol,temp->info.info);
        if(temp->info.short_info.short_info.fsrt!=NULL){
            printf(" %s , %s%-*c|",temp->info.short_info.short_info.fsrt,temp->info.short_info.short_info.scnd,l_short_info-(int)strlen(temp->info.short_info.short_info.fsrt)-(int)strlen(temp->info.short_info.short_info.scnd)+1,' ');
        }
        printf("\n");
        temp=temp->next;
    }

}
int longest_short_info(Events*root){
    size_t l;
    int max=0,sum=0;
    Events*temp=root;
    while(temp!=NULL){
        if(temp->info.short_info.short_info.fsrt!=NULL) {
            l = strlen(temp->info.short_info.short_info.fsrt);
            if ((int) l > max) {
                max = (int) l;
            }
        }
        temp=temp->next;
    }
    sum+=max;
    temp=root;
    max=0;
    while(temp!=NULL){
        if(temp->info.short_info.short_info.scnd!=NULL) {
            l = strlen(temp->info.short_info.short_info.scnd);
            if ((int) l > max) {
                max = (int) l;
            }
        }
        temp=temp->next;
    }
    sum+=max;
    return sum;
}
Events* longest_info(Events*root){
    size_t max=0,l;
    Events*max_field;
    Events*temp=root;
    while(temp!=NULL){
        l=strlen(temp->info.info);
        if(l>max) {
            max_field=temp;
            max = l;
        }
        temp=temp->next;
    }
    return max_field;
}
Events* longest_name(Events*root){
    size_t max=0,l;
    Events*max_field;
    Events*temp=root;
    while(temp!=NULL){
        l=strlen(temp->name);
        if(l>max) {
            max_field=temp;
            max = l;
        }
        temp=temp->next;
    }
    return max_field;
}

int amount_events(Events*root){
    Events*p;
    p=root;
    int num=0;
    while(p!=NULL){
        num++;
        p=p->next;
    }
    return num;
}
void output_one(Events**event){
    printf("------------------------\n");
    printf(" id: %d\n date: %s\n name: %s\n info: %s\n",
           (*event)->id,
           (*event)->date,
           (*event)->name,
           (*event)->info.info); // вывод значений
    if((*event)->info.short_info.short_info.fsrt!=NULL){
        printf(" Short info:\n %s\n %s\n",(*event)->info.short_info.short_info.fsrt,(*event)->info.short_info.short_info.scnd);
    }
    printf("------------------------\n");
}

void Remainder(char*dividend, char*divisor){
    int div_d, div_r;
    div_d=atoi(dividend);
    div_r=atoi(divisor);
    if(div_r%2!=0 || div_r>128){
        printf("Incorrect input\n");
        log_("Division error.");
        return;
    }
    union remainder rem;
    rem.num=div_d;
    switch(div_r){
        case 2:
            printf("%i %% 2 = %i",rem.num,rem.bit2);
            break;
        case 4:
            printf("%i %% 4 = %i",rem.num,rem.bit4);
            break;
        case 8:
            printf("%i %% 8 = %i",rem.num,rem.bit8);
            break;
        case 16:
            printf("%i %% 16 = %i",rem.num,rem.bit16);
            break;
        case 32:
            printf("%i %% 32 = %i",rem.num,rem.bit32);
            break;
        case 64:
            printf("%i %% 64 = %i",rem.num,rem.bit64);
            break;
        case 128:
            printf("%i %% 128 = %i",rem.num,rem.bit128);
            break;
    }

}

void log_(const char*format,...){
    FILE *file;
    char*parametr;
    parametr="a+";
    if(strcmp(format,"Program was launched.")==0){
        parametr="w";
    }
    file=fopen("log.txt",parametr);
    if(!file){
        printf("Error\n");
        return;
    }
    va_list args;
    va_start(args,format);
    int i=1;
    char buf[255];
    while(fgets(buf,255,file)!=NULL)
        i++;
    fprintf(file," %d.",i);
    vfprintf(file,format,args);
    int hours, minutes, seconds;
    time_t now; // арифметическое время
    time(&now);
    struct tm*local= localtime(&now);
    hours=local->tm_hour;
    minutes=local->tm_min;
    seconds=local->tm_sec;
    if (hours < 12) {    // до полудня
        fprintf(file," %02d:%02d:%02d am\n", hours, minutes, seconds);
    }
    else {    // после полудня
        fprintf(file," %02d:%02d:%02d pm\n", hours - 12, minutes, seconds);
    }
    fflush(file);
    va_end(args);
    fclose(file);
}

