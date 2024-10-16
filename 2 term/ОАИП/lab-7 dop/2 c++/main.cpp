#include "functions.h"

int main() {
    SetConsoleCP (1251);
    SetConsoleOutputCP (1251);
    setlocale(0,"");


    FILE *file;
    int choose;
    size_t l;
    do{
        printf("Choose option:\n1 - Clear\n2 - Add\n3 - Find\n4 - Close\n");
        scanf_s("%d",&choose);
        fflush(stdin);
        if(choose==1) {
            file=fopen("Dictionary.txt","w");
            fclose(file);
            continue;
        }
        if(choose==2) {

            while (1) {
                char word[255];
                printf("Do u want to enter a new couple of words in dictionary?\n1 - Yes\n2 - No\n");
                scanf_s("%d", &choose);
                fflush(stdin);
                if (choose == 1) {
                    printf("Input like that 'eng word'='rus word'\n");
                    fgets(word, 254, stdin);
                    fflush(stdin);
                    l = strlen(word);
                    word[l - 1] = ';';
                    for (int k = (int) l; k >= 0; k--)
                        word[k + 1] = word[k];
                    word[0] = ';';
                    file = fopen("Dictionary.txt", "at");
                    if (file == nullptr) {
                        printf("Error!\n");
                        _getch();
                        return 0;
                    }
                    fprintf(file, "%s", word);
                    fclose(file);
                }

                if (choose == 2)
                    break;
            }
            continue;
        }
        if(choose==3) {

            file = fopen("Dictionary.txt", "rt+");
            if (file == nullptr) {
                printf("Error!\n");
                _getch();
                return 0;
            }


            char *eng = nullptr;
            char *rus = nullptr;
            int len = 0;
            eng = (char *) calloc(1, sizeof(char));
            rus = (char *) calloc(1, sizeof(char));
            char h;
            int fl;
            unsigned char r;

            node *root = nullptr;
            h = ' ';
            do {
                fl = 0;
                while (h != ';' && h != EOF)
                    h = (char) fgetc(file);    //ликвидация лишнегo
                int i = 0;
                h = (char) fgetc(file);
                do {
                    if ((h == ' ' && eng[i - 1] == ' ')) {
                        fl = 1;
                        break;
                    }
                    if (if_letter_eng(h) == 0 && h != ' ') {
                        fl = 1;
                        break;
                    }

                    eng = (char *) realloc(eng, (len + 1) * sizeof(char));
                    eng[i] = h;
                    len++;
                    i++;
                    h = (char) fgetc(file);

                } while (h != '=' && h != EOF); //для английских слов

                if (fl == 1) {
                    while (h != ';' && h != EOF)
                        h = (char) fgetc(file);
                    h = ' ';
                    while (h != ';' && h != EOF)
                        h = (char) fgetc(file);
                    continue;
                }

                if (h == '=');
                else {
                    while (h != ';' && h != EOF)
                        h = (char) fgetc(file);
                    h = ' ';
                    while (h != ';' && h != EOF)
                        h = (char) fgetc(file);
                    continue;
                }


                int j = 0;
                len = 0;

                h = (char) fgetc(file);
                r = h;

                if (if_letter_rus(r) != 1) {
                    while (h != ';' && h != EOF)
                        h = (char) fgetc(file);
                    h = ' ';
                    while (h != ';' && h != EOF)
                        h = (char) fgetc(file);
                    continue;
                }
                fl = 0;

                while (h != ';' && h != EOF) { //для русских слов
                    r = h;

                    if ((h == ' ' && rus[j] == ' ')) { //пробелы
                        fl = 1;
                        break;
                    }

                    if (if_letter_rus(r) == 0 && h != ' ') {
                        fl = 1;
                        break;
                    }

                    rus = (char *) realloc(rus, (len + 1) * sizeof(char));
                    rus[j] = h;
                    len++;
                    j++;
                    h = (char) fgetc(file);
                }
                if (fl == 1) {
                    while (h != ';' && h != EOF)
                        h = (char) fgetc(file);
                    h = ' ';
                    while (h != ';' && h != EOF)
                        h = (char) fgetc(file);
                    continue;
                }
                eng[i] = '\0';
                rus[j] = '\0';
                create_dict(&root, eng, rus);
                h = (char) fgetc(file);
            } while (h != EOF);



            //print_dict(root);
            fflush(stdin);


            printf("Choose word in english to translate into russian:\n");
            char word[255];

            fgets(word, 254, stdin);
            l = strlen(word);
            word[l - 1] = '\0';

            node *found = find_element(root, word);
            if (found == nullptr) {
                printf("There are no coincidences.\n");

            }
            if (found != nullptr)
                printf("%s\t---\t%s\n", word, found->rus);
            fclose(file);

        }

    }while(1);

    _getch();


    return 0;
}
