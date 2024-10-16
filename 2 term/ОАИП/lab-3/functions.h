#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Events{
    int id;
    char *date;
    char *name;
    char*info;
}Events;

int check_int();
void check_1_or_2(int*choose);
void check_1_2_3_4_5_6(int*choose1);
void check_1_2_3(int*choose);
void check_days_week(int*day_week);
void check_id(Events*events,int*id,int size);


void output(Events *event);
void free_space(Events **events,int size);

void check_date(char*date,int fl,Events*events);
void Day_of_Week(const char*date,int day_week,Events*event,int fl, int *d, int *mo ,int *ye);

void add_event(Events** events,int*size,int fl);

int find_event(Events*events,int fl,int size);
int delete_events(Events*events,int *size);
int change_event(Events*events,int size, int *fl);
int func_sort_events_1(Events*events,int size);
int func_sort_events_several(Events*events,int size);
int find_name(Events*events,int size);


int check_int(){
    char ch;
    while((ch=(char)getchar())!='\n'){
        if(ch<'0'|| ch>'9'){
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
                printf("Wrong input\n");
                sr = -1;
                fflush(stdin);
            }
        }
    } while (sr == -1);
    fflush(stdin);
}

void check_1_2_3_4_5_6(int*choose1){
    int sr ;
    do {
        scanf_s("%d", choose1);
        sr = check_int();
        if (sr == 1) {
            if (*choose1 < 1 || *choose1 > 6) {
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
                printf("Wrong input\n");
                sr = -1;
                fflush(stdin);
            }
        }
    } while (sr == -1);
    fflush(stdin);
}

void check_days_week(int*day_week){
    int sr ;
    do {
        scanf_s("%d", day_week);
        sr = check_int();
        if (sr == 1) {
            if (*day_week < 0 || *day_week> 6) {
                printf("Wrong input\n");
                sr = -1;
                fflush(stdin);
            }
        }
    } while (sr == -1);
    fflush(stdin);
}

void check_id(Events*events,int*id,int size){
    int sr ;
    do {
        scanf_s("%d", id);
        sr = check_int();
        if (sr == 1) {
            if (*id< 0 || *id > events[size-1].id) {
                printf("Incorrect id\n");
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
                printf("Wrong input\n");
                sr = -1;
                fflush(stdin);
            }
        }
    } while (sr == -1);
    fflush(stdin);

}

void output(Events *event){
    printf("-----------------------\n");
    printf(" id: %d\n date: %s\n name: %s\n info: %s\n",
           event->id,
           event->date,
           event->name,
           event->info);
    printf("-----------------------\n");
}

void free_space(Events **events,int size){
    for(int i=0;i<size;i++){
        free((*events)[i].date);
        free((*events)[i].name);
        free((*events)[i].info);
    }
    free(*events);
}

void check_date(char*date,int fl,Events*events){
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
        check_date(date, fl,events);
    }
    int i = 0;
    while (date[i] != '\0') {
        if ((date[i] >= '0' && date[i] <= '9') || date[i] == '.')
            i++;
        else {
            printf("Date should consist of numbers and dotes\n");
            check_date(date, fl,events);
        }
    }
    int j = 0;
    char day[3], month[3], year[5];
    while (date[j] != '.') {
        if (j == 2) {
            printf("Wrong format, input like this [ _ _ . _ _ . _ _ _ _ ]\n");
            check_date(date, fl,events);
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
        check_date(date, fl,events);
    }
    month_ = atoi(month);
    if (month_ < 1 || month_ > 12) {
        printf("Wrong month\n");
        check_date(date, fl,events);
    }
    year_ = atoi(year);
    if (year_ < 1 || year_ > 3000) {
        printf("Wrong year\n");
        check_date(date, fl,events);
    }
    if(month_==2 && year_%4==0 && day_>29){
        printf("Wrong day\n");
        check_date(date, fl,events);
    }
    if(month_==2 && year_%4!=0 && day_>28){
        printf("Wrong day\n");
        check_date(date, fl,events);
    }
}

void Day_of_Week(const char*date,int day_week,Events*event,int fl, int *d, int* mo, int *ye){
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
    int day_, month_, year_;

    day_ = atoi(day);
    month_ = atoi(month);
    year_ = atoi(year);

    if(fl==1) {
        int a = (14 - month_) / 12;
        int y = year_ - a;
        int m = month_ + 12 * a - 2;
        int day_of_week = (7000 + (day_ + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) % 7;
        if (day_of_week == day_week)
            output(event);
    }
    if(fl==0){
        *d=day_;
        *mo=month_;
        *ye=year_;
    }
}

void add_event(Events**events,int *size,int fl){
    while(1) {
        int i=*size-1;
        printf("///////////////////////\n");
        printf("The %d event:\n", i + 1);
        printf("-----------------------\n");
        (*events)[i].id = i + 1;
        char buf[255];
        check_date(buf, fl,*events);
        (*events)[i].date = (char *) calloc(11, sizeof(char));
        strcpy((*events)[i].date, buf);
        printf("Name: ");
        fgets(buf, 253, stdin);
       fflush(stdin);
       size_t len;
       len=strlen(buf);
       buf[len-1]='\0';
        (*events)[i].name = (char *) calloc(strlen(buf) + 1, sizeof(char));
        strcpy((*events)[i].name, buf);
        printf("Info: ");
        fgets(buf, 253, stdin);
        fflush(stdin);
        len=strlen(buf);
        buf[len-1]='\0';
        (*events)[i].info = (char *) calloc(strlen(buf) + 1, sizeof(char));
        strcpy((*events)[i].info, buf);
        printf("-----------------------\n");
        printf("Do u want to add one more event?\n1 - Yes\n2 - No\n");
        int choose;
        check_1_or_2(&choose);

        if(choose ==2)
            break;
        else {
            *size+=1;
            *events=(Events*)realloc(*events,(*size)*sizeof(Events));
        }
    }

}

int find_event(Events*events,int fl,int size) {
    if(size==0){
        printf("-----------------------\n");
        printf("There are no events\n");
        return -1;
    }
    char date[255];
    while(1){
        printf("-----------------------\n");
        printf("Choose how u want to find an event:\n1 - by date\n2 - by day of the week\n3 - stop\n");
        int choose;
        check_1_2_3(&choose);
        if (choose == 1) {
            fl=0;

                printf("-----------------------\n");
                printf("Choose the date [ _ _ . _ _ . _ _ _ _ ] of the event u want to be printed\nYear is lower that 3000\n");
                check_date(date, fl,events);
                int count = 0;
                for (int k = 0; k < size; k++) {
                    int same;
                    int i = 0, j = 0;
                    while (date[i]!='\0') {
                        if (date[i] == events[k].date[j]) {
                            same = 1;
                            i++;
                            j++;
                        } else {
                            same = 0;
                            break;
                        }
                    }
                    if (same == 0) {
                        continue;
                    } else {
                        count++;
                        output(&events[k]);
                    }
                }
                if (count == 0) {
                    printf("-----------------------\nThere are no coincidences\n-----------------------\n");
                }
                fflush(stdin);
                /*printf("Should we continue?\n1 - Yes\n2 - No\n");
                int choice;
                check_1_or_2(&choice);
                if (choice == 2)
                    break;
            }*/
        }
        if (choose == 2) {
            fl=1;
            printf("-----------------------\n");
            printf("Choose a day of the week:\n1 - Monday\n2 - Tuesday\n3 - Wednesday\n4 - Thursday\n5 - Friday\n6 - Saturday\n0 - Sunday\n");
            int day_week;
            check_days_week(&day_week);
            for (int i = 0; i < size; i++) {
                Day_of_Week(events[i].date, day_week, &events[i],fl,0,0,0);
            }
        }
        if (choose == 3)
            break;
    }
    return 1;
}

int delete_events(Events*events,int *size){
    if(*size==0){
        printf("-----------------------\n");
        printf("There are no events.\n");
        return -1;
    }
    int id;

    if(find_name(events,*size)==-1)
        return -1;

  //  printf("Choose the id of the event or 0 to skip\n");
    check_id(events, &id, *size);
    if(id==0){
        delete_events(events,size);
    }
    printf("-----------------------\n");
    printf("Event that u want to delete\n");
    output(&events[id - 1]);



    printf("-----------------------\n");
    printf("Your events except %d:\n",id);
    for(int i=0;i<*size;i++){
        if(events[i].id==id){
            for(int j=i;j<*size-1;j++){
                events[j]=events[j+1];
            }
            *size-=1;
            events=(Events*)realloc(events,(*size)*sizeof(Events));
            for(int k=0;k<*size;k++)
                events[k].id=k+1;
            break;
        }
    }
    for(int i=0;i<*size;i++)
        output(&events[i]);
    return 1;
}

int change_event(Events*events,int size, int *fl){
    if(size==0){
        printf("-----------------------\n");
        printf("There are no events\n");
        return -1;
    }
    printf("-----------------------\n");
    int id;
    if(find_name(events,size)==-1)
        return -1;
   // printf("Choose the id of the event\n");
    check_id(events, &id, size);
    if(id==0){
        change_event(events,size,fl);
    }
    printf("-----------------------\n");
    printf("Event that u want to change\n");
    output(&events[id - 1]);

    while(1) {
       printf("-----------------------\n");
        printf("Choose the field:\n1 - Date\n2 - Name\n3 - Info\n4 - Stop\n");
        int choose;
        size_t len;
        char buf[255];
        check_1_2_3_4(&choose);
        if (choose == 1) {
            *fl = 1;
            check_date(buf, *fl,events);
            //fflush(stdin);
            events[id - 1].date = (char *) realloc(events[id-1].date,11*  sizeof(char));
            strcpy(events[id - 1].date, buf);
            continue;
        }
        if (choose == 2) {
            printf("New name: ");
            fgets(buf, 253, stdin);
           // fflush(stdin);
           len=strlen(buf);
           buf[len-1]='\0';
            events[id - 1].name = (char *) realloc(events[id - 1].name, (strlen(buf) + 1) * sizeof(char));
            strcpy(events[id - 1].name, buf);
            continue;
        }
        if (choose == 3) {
            printf("New info: ");
            fgets(buf, 253, stdin);
           // fflush(stdin);
            len=strlen(buf);
            buf[len-1]='\0';
            events[id - 1].info = (char *) realloc(events[id - 1].info, (strlen(buf) + 1) * sizeof(char));
            strcpy(events[id - 1].info, buf);
            continue;
        }
        if (choose == 4) {
            printf("-----------------------\n");
            printf("Changed event:\n");
            output(&events[id-1]);
            break;
        }
    }
    return 1;
}

int func_sort_events_1(Events *events,int size){
    if(size==0) {
        printf("-----------------------\n");
        printf("There are no events\n");
        return -1;
    }
            printf("-----------------------\n");
            printf("Choose the field to sort events:\n1 - Date\n2 - Name\n3 - Info\n");
            int choose;
            check_1_2_3(&choose);
            int fl;
            Events temp;
            for (int gap = size / 2; gap > 0; gap /= 2) {
                do {
                    fl = 0;
                    for (int i = 0, j = gap; j < size; i++, j++) {
                        if (choose == 1) {
                            int d1, m1, y1;
                            int d2, m2, y2;
                            Day_of_Week(events[i].date, 0, &events[i], 0, &d1, &m1, &y1);
                            Day_of_Week(events[j].date, 0, &events[j], 0, &d2, &m2, &y2);
                            if (y1 > y2 || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2)) {
                                temp = events[i];
                                events[i] = events[j];
                                events[j] = temp;
                                fl = 1;
                            }

                        }
                        if (choose == 2) {
                            if (strcmp(events[j - 1].name, events[j].name) > 0) {
                                temp = events[j - 1];
                                events[j - 1] = events[j];
                                events[j] = temp;
                                fl=1;

                            }

                        }
                        if (choose == 3) {
                            if (strcmp(events[i].info, events[j].info) > 0) {
                                temp = events[i];
                                events[i] = events[j];
                                events[j] = temp;
                                fl = 1;
                            }
                        }

                    }

                } while (fl);
            }

    for (int i = 0; i < size; i++)
        output(&events[i]);
    return 1;
}

int func_sort_events_several(Events*events,int size) {
    if (size == 0) {
        printf("-----------------------\n");
        printf("There are no events\n");
        return -1;
    }
    int choose;
    printf("Choose by which fields you want to sort:\n");
    printf("1 - Date && Name\n2 - Date && Info\n3 - Name && Info\n4 - All\n");
    check_1_2_3_4(&choose);
    int fields[4];
    for(int i=0;i<4;i++)
        fields[i]=0;
    fields[choose-1]=1;
    int fl;
    Events temp;
    for (int gap = size / 2; gap > 0; gap /= 2) {
        do {
            fl = 0;
            for (int i = 0, j = gap; j < size; i++, j++) {
                int d1, m1, y1;
                int d2, m2, y2;
                Day_of_Week(events[i].date, 0, &events[i], 0, &d1, &m1, &y1);
                Day_of_Week(events[j].date, 0, &events[j], 0, &d2, &m2, &y2);
                if ((y1 > y2 || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2))&&(fields[0]==1 || fields[1]==1 || fields[3]==1)) {
                    temp = events[i];
                    events[i] = events[j];
                    events[j] = temp;
                    fl = 1;
                }
                else if ((y1 == y2 && m1 == m2 && d1 == d2 && (fields[0]==1 || fields[3]==1) )|| fields[2]==1 ) {
                    if (strcmp(events[i].name, events[j].name) > 0) {
                        temp = events[i];
                        events[i] = events[j];
                        events[j] = temp;
                        fl = 1;
                    }

                    else if ((strcmp(events[i].name, events[j].name) == 0 && (fields[1]==1 || fields[2]==1))|| fields[3]==1)
                    {
                        if (strcmp(events[i].info, events[j].info) > 0) {
                            temp = events[i];
                            events[i] = events[j];
                            events[j] = temp;
                            fl = 1;
                        }
                    }
                }
            }
        } while (fl);

    }
    for (int i = 0; i < size; i++)
        output(&events[i]);
    return 1;
}

int  find_name(Events*events,int size){
    printf("Input the name of the event:\n");
    char *name;
    char buf[255];
    fgets(buf,254,stdin);
    size_t len;
    len=strlen(buf);
    buf[len-1]='\0';
    name=(char*)malloc((len-1)*sizeof(char));
    strcpy(name,buf);
    printf("Choose the id of needed event or other id if u know it.\nOr choose 0 to return back.\n");
    printf("-----------------------\n");
    int count=0;
    for(int i=0;i<size;i++){
        char *ptr;
            ptr=strstr(events[i].name,name);
            if (ptr==NULL)
                continue;
            if(ptr-events[i].name+1!=1)
                continue;
            else {
                    count++;
                output(&events[i]);
            }
        }

    if(count==0){
        printf("There are no coincidences\n");
        return -1;
    }
    fflush(stdin);
    return 1;
}



