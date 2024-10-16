#include "functions.h"

int main() {
    Events *events = NULL;
    FILE *file;
    int size = 0;
    int fl = 1;
    int choose;
    events = (Events *) calloc(size, sizeof(Events));
    while (1) {
        fl = 0;
        printf("-----------------------\n");
        printf("Choose the right option:\n1 - Add event\n2 - Find\n3 - Delete\n4 - Change\n5 - Sort\n6 - Close +(Save in a binary file)\n");
        int choose1;
        check_1_2_3_4_5_6(&choose1);
        if (choose1 == 1) {
            fl = 1;
            printf("Choose:\n1 - By keyboard\n2 - By file\n");
            check_1_or_2(&choose);
            if (choose == 1) {
                if (size == 0) {
                    size = 1;
                    events = (Events *) calloc(size, sizeof(Events));
                    add_event(&events, &size, fl);
                } else {
                    size += 1;
                    events = (Events *) realloc(events, size * sizeof(Events));
                    add_event(&events, &size, fl);
                }
            }
            if (choose == 2) {
                file = fopen("C:/For bins/Save.bin", "rb");
                if (file == NULL) {
                    printf("File cant be opened\n");
                    fflush(stdin);
                    continue;
                }
                    rewind(file);
                    int n;
                    fread((char *) &n, sizeof(int), 1, file);
                    for (int i = 0; i < n; i++) {
                        if(size!=0) {
                            size++;
                            events = (Events *) realloc(events, (size) * sizeof(Events));
                        }
                        if(size==0){
                            size=1;
                            events=(Events*)calloc(size,sizeof(Events));
                        }

                        fread(&(events[size - 1].id), sizeof(int), 1, file);
                        events[size - 1].id=size;

                        size_t len;
                        fread((char *) &len, sizeof(size_t), 1, file);
                        events[size - 1].date = (char *) malloc((len + 1) * sizeof(char));
                        fread(events[size - 1].date, sizeof(char), len, file);
                        events[size - 1].date[len] = '\0';

                        fread((char *) &len, sizeof(size_t), 1, file);
                        events[size - 1].name = (char *) malloc((len + 1) * sizeof(char));
                        fread(events[size - 1].name, sizeof(char), len, file);
                        events[size - 1].name[len] = '\0';

                        fread((char *) &len, sizeof(size_t), 1, file);
                        events[size - 1].info = (char *) malloc((len + 1) * sizeof(char));
                        fread(events[size - 1].info, sizeof(char), len, file);
                        events[size - 1].info[len] = '\0';

                    }
                    fclose(file);

            }
        }
        if (choose1 == 2) {
                int result = find_event(events, fl, size);
                if (result == -1)
                    continue;
            }
        if (choose1 == 3) {
                int result = delete_events(events, &size);
                if (result == -1)
                    continue;
            }
        if (choose1 == 4) {
                int result = change_event(events, size, &fl);
                if (result == -1)
                    continue;
            }
        if (choose1 == 5) {
                printf("Choose the type of sort:\n1 - One field\n2 - Several field\n");
                check_1_or_2(&choose);
                if (choose == 1) {
                    int result = func_sort_events_1(events, size);
                    if (result == -1)
                        continue;
                }
                if (choose == 2) {
                    int result = func_sort_events_several(events, size);
                    if (result == -1)
                        continue;
                }
            }
        if (choose1 == 6)
                break;
        }

        file = fopen("C:/For bins/Save.bin", "wb+");
        rewind(file);
        fwrite((char *) &size, sizeof(int), 1, file);
        size_t len;
        for (int i = 0; i < size; i++) {
            fwrite((char *) &events[i].id, sizeof(int), 1, file);

            len = strlen(events[i].date);
            fwrite((char *) &len, sizeof(size_t), 1, file);
            fwrite(events[i].date, sizeof(char), len, file);

            len = strlen(events[i].name);
            fwrite((char *) &len, sizeof(size_t), 1, file);
            fwrite(events[i].name, sizeof(char), len, file);

            len = strlen(events[i].info);
            fwrite((char *) &len, sizeof(size_t), 1, file);
            fwrite(events[i].info, sizeof(char), len, file);
        }

    fclose(file);
    free_space(&events, size);
    _getch();
    return 0;

}

