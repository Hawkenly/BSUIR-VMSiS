#include "functions.h"

int main(){
    stack*head=NULL;
    char*expression;
    char*str_out=NULL;
    int h;

    do {
        get_str(&expression);
        h = check_str(expression);
    }while(h);
    rpn(expression,&str_out,&head);
    printf("Reverse polish notation:\n");
    printf("%s",str_out);
    _getch();
    return 0;
}