#include "functions.h"
int task1() {
	printf("Fill the array from the keyboard with real numbers. Remove all integers\n");
	float* arr;
	int n=0;
	printf("Input the size of array\n");

	memory_array(&arr,&n);
	fill_array(arr, &n);
	delete_integer(arr, &n);
	output_array(arr, &n);
	free_array(arr);

	return 0;
}

int task2() {
	printf("In an NxM matrix, delete all elements on the secondary diagonal\n");
	int** matrix;
	int N = 0, M = 0;
	printf("Input the sizes of the matrix one by one\n");

	memory_matrix(&matrix, &N, &M);
	input_matrix(matrix, &N, &M);
	delete_elements(matrix, &N, &M);
	output_matrix(matrix, &N, &M);
	free_matrix(matrix, &N);

	return 0;
}
int task3() {
	printf("In a two-dimensional array (the number of numbers in a line can be different, the last number is -100.) Duplicate an odd element in each even line\n");
	int** mas;
	int N = 0;
	printf("Input the number of lines in your array:\n");

	memory_non_matrix(&mas, &N);
	double_odd_element(mas, N);
	output_non_matrix(mas, N);
	free_non_matrix(mas, N);

	return 0;
}