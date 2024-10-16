#include "Functions.h"
int task1() {
	int matrix[100][100];
	int n = 0, m = 0;
	int choose = 0;
	int col = 0, zero = 0;
	int general_ident = 1, ident = 1, num = 0, column_arr[100], column = 0, max = 0;
	printf("There is an integer rectangular matrix. Determine the number of lines containing at least one null element; the number of the column containing the longest series of identical elements.\n\n");
	printf("Choose the way to full the matrix : 1 - by the keyboard, 2 - by random values, 3 - If u want to close this program\n");
	choose_input(&choose);
	if (choose == 1) keyboard_input(matrix, &n, &m);
	if (choose == 2) random_input(matrix,&n,&m);
	if (choose == 3) main();
	//Поиск нулевого эл-та в строке
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) 
			if (matrix[i][j] == 0) {
				col++;
				break;
			}
	//Пробегание по столбцам	
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			num = matrix[i][j];
			for (int k = i + 1; k < n; k++) {//Сравнение эл-ов
				if (num == matrix[k][j]) 
					ident++;//Кол-во равных
			}
			if (ident > general_ident)
				general_ident = ident;//Макс. равных
		}
		column_arr[j] = general_ident;//запись количества равных в массив 
		general_ident = 1;
		ident = 1;
	}
	max = column_arr[0];
	column = 0;
	for (int i = 0; i < m; i++)
		if (column_arr[i] > max)
			column = i;
	printf("The amount of the lines which has at least one null element is: %d\n",col);
	printf("The number of the column which is containing the longest series of identical elements is: %d\n",column);
	return 0;
}
int task2() {
	int n = 0, m = 0, choose = 0,col=0;
	int matrix[100][100];
	int column = 0;
	printf("Find the first column in the matrix, all elements of which are positive. The signs of the elements of the previous column are reversed.\n\n");
	printf("Choose the way to full the matrix : 1 - by the keyboard, 2 - by random values, 3 - If u want to close this program\n");
	choose_input(&choose);
	if (choose == 1) keyboard_input(matrix, &n, &m);
	if (choose == 2) random_input(matrix,&n,&m);
	if (choose == 3) main();
	//Поиск всего положительного столбца
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			if (matrix[i][j] <= 0) break;
			else col++;
		}
		if (col == n) {
			column = j;//Номер этого столбца
			if(column>0) 
				for (int i = 0; i < n; i++) {
				matrix[i][column - 1] = 0- matrix[i][column - 1];//Меняем эл-ты предыдущего столбца на противоположные
			}
			break;
		}
		col = 0; 
	}
	printf("The result is:\n");
	output_matrix(matrix, &n, &m);
	return 0;
}
int task3() {
	int choose = 0, n = 0,max=0;
	int matrix[100][100];
	printf("In the square NxN matrix, find the maximum element in the 1st zone.\n\n");
	printf("Choose the way to full the matrix : 1 - by the keyboard, 2 - by random values, 3 - If u want to close this program\n");
	choose_input(&choose);
	if (choose == 1) keyboard_input3(matrix, &n);
	if (choose == 2) random_input3(matrix, &n);
	if (choose == 3) main();

	max = matrix[0][0];
	if (n % 2 == 0)//Для м-цы с четным числом строк и столбцов
		for (int i = 0; i < n / 2; i++)
			for (int j = 0; j < n / 2; j++)
				if (matrix[i][j] > max)
					max = matrix[i][j];
	if (n%2==1)//Для м-цы с нечетным числом строк и столбцов
		for (int i = 0; i < (n+1) / 2; i++)
			for (int j = 0; j < (n+1) / 2; j++)
				if (matrix[i][j] > max)
					max = matrix[i][j];

	printf("The max element in the 1st zone is:\n %d", max);
	return 0;
}

