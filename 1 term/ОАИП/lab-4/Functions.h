#include<stdio.h>
#include<stdlib.h>

void choose_menu(int* mchoose); //
void size_matrix(int* n, int* m);//
void size_matrix3(int* n);//
void check_int(int* element);//
void choose_input(int* choose);//
void keyboard_input(int matrix[100][100], int* n, int* m);//
void keyboard_input3(int matrix[100][100], int* n);//
void random_input(int matrix[100][100], int* n, int* m);//
void random_input3(int matrix[100][100], int* n);//
void output_matrix(int matrix[100][100], int* n, int* m);//
void output_matrix3(int matrix[100][100], int* n);//

void choose_menu(int*mchoose) {//Выбор задания
	scanf_s("%d", mchoose);
	char ch;
	while (ch = getchar() != '\n') 
		if (ch < '1' || ch>'4') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", mchoose);
		}
	if ((*mchoose) < 1 || (*mchoose)>4) {
		printf("Wrong input\n");
		choose_menu(mchoose);
	}
}
//Размеры матриц
void size_matrix(int* n, int* m) {
	printf("Input the size of the matrix one by one:\n");
	scanf_s("%d", n);
	scanf_s("%d", m);
	char ch;
	while(ch=getchar()!='\n')
		if (ch < '0' || ch>'9') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", n);
			scanf_s("%d", m);
		}
	if (((*n) < 1 || (*n) > 100) || ((*m) < 1 || (*m) > 100)) {
		printf("Wrong input\n");
		size_matrix(n, m);
	}
}
void size_matrix3(int* n) {
	printf("Input the size of the square matrix:\n");
	scanf_s("%d",n);
	char ch;
	while (ch = getchar() != '\n')
		if (ch < '0' || ch>'9') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", n);
		}
	if (((*n) < 1 || (*n) > 100) ){
		printf("Wrong input\n");
		size_matrix3(n);
	}
}
void check_int(int* element) { // Проверка ввода числа в матрицу
	scanf_s("%d", element);
	char ch;
	while (ch = getchar() != '\n') {
		if (ch < '0' || ch>'9') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", element);
		}
	}
}
void choose_input(int* choose) {//Выбор метода заполнения м-цы
	scanf_s("%d", choose);
	char ch;
	while (ch = getchar() != '\n')
		if (ch < '1' || ch>'3') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", choose);
		}
	if ((*choose) < 1 || (*choose) > 4) {
		printf("Wrong input\n");
		choose_input(choose);
	}
}
//Ввод м-цы с клавиатуры
void keyboard_input(int matrix[100][100], int* n, int* m) {
	size_matrix(n, m);
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *m; j++) {
			printf("Input the element [%d][%d] of the matrix:\n", i, j);
			check_int(&matrix[i][j]);
		}
}
void keyboard_input3(int matrix[100][100], int* n) {
	size_matrix3(n);
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *n; j++) {
			printf("Input the element [%d][%d] of the matrix:\n", i, j);
			check_int(&matrix[i][j]);
		}
}
//Рандомное заполнение м-цы
void random_input(int matrix[100][100], int* n, int* m) {
	int sign=0, choice=0;
	srand(time(NULL));
	size_matrix(n, m);
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *m; j++) {
			choice = rand() % 2;
			if (choice == 0) sign = -1;
			else sign = 1;
			matrix[i][j] = (rand() % 10) *sign;
		}
	printf("Your matrix : \n");
	output_matrix(matrix, n, m);
}
void random_input3(int matrix[100][100], int* n) {
	int sign = 0, choice = 0;
	srand(time(NULL));
	size_matrix3(n);
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *n; j++) {
			choice = rand() % 2;
			if (choice == 0) sign = -1;
			else sign = 1;
			matrix[i][j] = (rand() % 10) * sign;
	
		}
	printf("Your matrix : \n");
	output_matrix3(matrix, n);
}
//Вывод м-ц
void output_matrix(int matrix[100][100], int* n, int* m) {
	for (int i = 0; i < *n; i++) {
		for (int j = 0; j < *m; j++)
			printf("%2d ", matrix[i][j]);
		printf("\n");
	}
}
void output_matrix3(int matrix[100][100], int* n) {
	for (int i = 0; i < *n; i++) {
		for (int j = 0; j < *n; j++)
			printf("%2d", matrix[i][j]);
		printf("\n");
	}
}
