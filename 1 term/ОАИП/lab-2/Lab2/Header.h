#include <stdio.h>
int inputint(int n){
	char ch;
	while ((ch = getchar()) != '\n') 
		if (ch < 48 || ch > 57) {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", &n);
		}
	return n;
}