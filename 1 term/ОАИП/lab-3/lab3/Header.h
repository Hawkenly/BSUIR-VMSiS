#include<stdio.h>
#include<stdlib.h>

void menu_choose(int* menu);
void input_choose(int* choose);
void keyboard_input(int* n, float* arr);
void random_input(int* n, float* arr);
void size_of_arr(int *n);
void check_element(float* element);
void inputint(int* k,int*fl);
void keyboard_input3(char* num1s, char* num2s, int* num1,int*num2,int*length, int*length1,int* length2);
void keyboard_firstnum(char* num1s, int* num1, int* length, int* length1);
void keyboard_secondnum(char* num2s, int* num2, int* length2 );
void random_input3(int* num1, int* num2, int* length);
//Функции для 1 и 2 задач

void keyboard_input(int* n,float *arr) { // Ввод с клавиатуры
	printf("Input the number of elements from 1 to 100 :\n");
	size_of_arr(n);
	for (int i = 0; i <  *n; i++) {
		printf("Input the %d element of array :\n", i);
		scanf_s("%f", &arr[i]);
		check_element(&arr[i]);
	}
}

void random_input(int*n, float* arr) { //Рандомный ввод
	float fract = 0.0;
	srand(time(NULL));
	printf("Input the number of elements :\n");
	size_of_arr(n);
	for (int i = 0; i < *n; i++) {

		fract = (rand() % 1000) / 1000.0;
		arr[i] = (rand() % 1000)+ fract;
	}
	printf("Your array : ");
	for (int i = 0; i < *n; i++)
		printf("%.3f ", arr[i]);
	printf("\n");
}

void size_of_arr(int* n) {  //Ввод размера массива                                            
	char ch;
	scanf_s("%d", n);
	while ((ch = (char)getchar()) != '\n')
		if (ch < '0' || ch > '9') {
			printf("Please, input a natural number\n");
			rewind(stdin);
			scanf_s("%d", n);
		}
	if (*n < 1 || *n>100) {
		printf("Input a number from 1 to 100\n");
		size_of_arr(n);
	}
}

void check_element(float *element) { //Проверка на ввод э
	char ch;
	while ((ch = (char)getchar()) != '\n') {
		if ((ch >= '0' && ch <= '9') || ch == '.' || ch == '-') ;
		else {
			printf("Not a number\n");
			rewind(stdin);
			scanf_s("%f", element);
		}
	}
}
//Функция для всех задач
void input_choose(int* choose) {
	char ch;
	scanf_s("%d", choose);
	while ((ch = (char)getchar()) != '\n')
		if (ch < '1' || ch > '3') {
			printf("Try again\n");
			rewind(stdin);
			scanf_s("%d", choose);
		}
	if (*choose < 1 || *choose >3) {
		printf("Wrong input\n");
		input_choose(choose);
	}
}
//Функция для main
void menu_choose(int* choose_menu) {
	char ch;
	scanf_s("%d", choose_menu);
	while ((ch = (char)getchar()) != '\n')
		if (ch < '1' || ch > '4') {
			printf("Try again\n");
			rewind(stdin);
			scanf_s("%d", choose_menu);
		}
	if (*choose_menu < 1 || *choose_menu >4) {
		printf("Wrong input\n");
		menu_choose(choose_menu);
	}
}
//Функция для 2й задачи
void inputint(int* k,int*fl) {
	printf("Input k to delete each k element:\n");
	scanf_s("%d", k);
	char ch;
	while ((ch = (char)getchar()) != '\n')
		if ((ch < '0' || ch > '9') ) {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", k);
		}
	if (*k == 0) (*fl) = 1;
	if (*k < 0) inputint(k, fl);
}
//Функции для 3й задачи
void keyboard_input3(char* num1s, char* num2s, int* num1, int* num2, int* length, int* length1, int* length2) {
	printf("Input the first number\n");
	keyboard_firstnum(num1s,  num1, length,  length1);
	printf("Input the second number\n");
	keyboard_secondnum(num2s, num2, length2);
}
void keyboard_secondnum(char* num2s, int* num2, int* length2) {
	gets(num2s);
	(*length2) = 0;
	if (num2s[0] == '-') {
		printf("Please, input the positive number\n");
		keyboard_secondnum(num2s, num2, length2);
	}
	
	if (num2s[0] == '0') {
		printf("Input the number is not starting with 0\n");
		keyboard_secondnum(num2s, num2, length2);
	}
	for (int i = 0; num2s[i] != '\0'; i++) {
		(*length2)++;
		if ((num2s[i] < '0' || num2s[i]> '9')) {
			printf("Not a number\n");
			keyboard_secondnum(num2s, num2, length2);
		}
		num2[i] = num2s[i] - '0';
	}
	if ((*length2) != 30 ) {
		printf("Input a thirty-digit number\n");
	
		keyboard_secondnum(num2s, num2, length2);
	}
	
}
	
void keyboard_firstnum(char* num1s, int* num1, int* length, int* length1) {
	gets(num1s);
	(*length1) = 0;
		if (num1s[0] == '-') {
			printf("Please, input the positive number\n");
			keyboard_firstnum(num1s, num1, length, length1);
		}
		if (num1s[0] == '0') {
			printf("Input the number is not starting with 0\n");
			keyboard_firstnum(num1s, num1, length, length1);
		}
		for (int i = 0; num1s[i] != '\0'; i++) {
			(*length1)++;
			if (num1s[i] < '0' || num1s[i] > '9')
			 {
				printf("Not a number\n");
				keyboard_firstnum(num1s, num1, length, length1);
			}
			num1[i] = num1s[i] - '0';
		}
		(*length) = (*length1);
		if ((*length1) != 30 ) {
			printf("Input a thirty-digit number\n");
			keyboard_firstnum(num1s, num1, length, length1);
		}

	}
void random_input3( int* num1,int*num2,int*length) {
	srand(time(NULL));
	(*length) = 30;
	for (int i = 0; i < 30; i++) {
		num1[i] = rand() % 10;
		while (num1[i] == 0) num1[i] = rand() % 10;
	}
	printf("Your first number  : ");
	for (int i = 0; i < 30; i++)
		printf("%d", num1[i]);
	printf("\n");

	for (int i = 0; i < 30; i++) {
		num2[i] = rand() % 10;
		while (num2[i] == 0) num2[i] = rand() % 10;
	}

	printf("Your second number : ");
	for (int i = 0; i < 30; i++)
		printf("%d", num2[i]);
	printf("\n");
}