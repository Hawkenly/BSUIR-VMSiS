#include "Header.h"

int task1() {
	printf("In a one-dimensional array, sort the even elements using the selection method\n");
	int* arr=NULL;
	int n = 0;
	printf("Input the amount of elements of the array:\n");
	memory_arr(&arr,&n);
	fill_arr(arr, n);
	selection_sort(arr, n);
	out_arr(arr, n);
	clear(arr);
	return 0;
}

int task2() {
	printf("In an NxM matrix, sort rows in ascending order of the sum of even elements using the merge method\n");
	int** arr=NULL;
	int n = 0, m = 0;
	printf("Input the sizes of the matrix one by one\n");
	Memory_matrix(&arr, &n, &m);
	Fill_matrix(arr, n, m);
	int left = 0; int right = n;
	merge_sort_rows(arr, left, right,m,n);
	
	

	return 0;
}