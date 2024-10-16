#include <stdio.h>
#include <stdlib.h>
void menu(int* menu_choice);

void memory_arr(int** arr,int *n);
void fill_arr(int* arr, int n);
void selection_sort(int* arr, int n);
void find_min(int* arr, int n, int start, int* min);
void out_arr(int* arr, int n);
void clear(int* arr);

void Memory_matrix(int*** arr, int* n, int* m);
void Fill_matrix(int** arr, int n, int m);
void choosee(int* choose);
void random(int** arr, int n, int m);
void keyboard(int** arr, int n, int m);
void merge_sort_rows(int** arr, int left, int right, int m,int n);
void find_min_row(int** arr, int n, int m, int* min, int start);
void merge(int** arr, int left, int mid, int right, int m,int n);
void double_matrix(int*** arr, int n);
void return_matrix(int*** arr, int n);
void Out_matrix(int** arr, int n, int m);


void menu(int* menu_choice) {
	scanf_s("%d", menu_choice);
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch < '1' || ch>'3') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", menu_choice);
		}
	}
	if (*menu_choice < 1 || *menu_choice>3) {
		printf("Wrong input\n");
		menu(menu_choice);
	}
}

void memory_arr(int** arr,int *n) {
	scanf_s("%d", n);
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch < '0' || ch>'9') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", n);
		}
	}
	if (*n < 1) {
		printf("Wrong input\n");
		memory_arr(arr,n);
	}
	*arr = (int*)calloc(*n, sizeof(int));
	
}

void fill_arr(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("Input element [%d]:\t", i);
		int sc= scanf_s("%d", &arr[i]);
		while (sc == 0) {
			printf("Wrong nput\n");
			rewind(stdin);
			sc= scanf_s("%d", &arr[i]);
		}
		char ch;
		while ((ch = getchar()) != '\n') {
			if (ch < '0' || ch>'9') {
				printf("Wrong input\n");
				rewind(stdin);
				scanf_s("%d", &arr[i]);
			}
		}
		while (sc == 0) {
			printf("Wrong input\n");
			rewind(stdin);
			sc = scanf_s("%d", &arr[i]);
		}
	}
}

void selection_sort(int* arr, int n) {
	int min = 0;
	int temp = 0;
	for (int i = 0; i < n-1; i++) {
		if (arr[i] % 2 == 0) {
			find_min(arr, n, i, &min);
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
	}


void find_min(int* arr, int n, int start, int* min) {
	*min = start;
	for (int i = start; i < n; i++)
		if ((arr[i] % 2 == 0) && (arr[i] < arr[*min])) {
			*min = i;
		}
}
	
void out_arr(int* arr, int n) {
	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);
}
void clear(int* arr) {
	free(arr);
}

void Memory_matrix(int*** arr, int* n, int* m) {
	scanf_s("%d", n);
	scanf_s("%d", m);
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch < '0' || ch>'9') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", n);
			scanf_s("%d", m);
		}
	}
	if (*n <= 0 || *m <= 0) {
		printf("Wrong input\n");
		Memory_matrix(arr, n, m);
	}
	*arr = (int**)calloc(*n, sizeof(int*));
	for (int i = 0; i < *n; i++)
		(*arr)[i] = (int*)calloc(*m, sizeof(int));
}

void Fill_matrix(int** arr, int n, int m) {
	int choose = 0;
	printf("Choose how to fill the matrix:\n 1 - by random values\n 2 - by keyboard\n");
	choosee(&choose);
	
	
	
	
	
	if (choose == 1) random(arr, n, m);
		
	if (choose == 2) keyboard(arr, n, m);
		
			
			
	printf("Your matrix:\n");
	Out_matrix(arr, n, m);
}

void choosee(int* choose) {
	
	scanf_s("%d", choose);
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch < '1' || ch>'2') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", choose);
		}
	}
	if (*choose < 1 || *choose>2) {
		printf("Wrong input\n");
		choosee(choose);
	}

}
void random(int** arr, int n, int m) {
	int znak = 0;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			arr[i][j] = rand() % 10;
			znak = rand() % 2;
			if (znak == 0) znak = -1;
			else znak = 1;
			arr[i][j] = arr[i][j] * znak;
		}

}
void keyboard(int** arr, int n, int m) {

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			printf("Input element [%d][%d]:\t", i, j);
			
				int sc = scanf_s("%d", &arr[i][j]);
				while (sc == 0) {
					printf("Wrong input\n");
					rewind(stdin);
					sc = scanf_s("%d", &arr[i][j]);
				}
				char ch;
				while ((ch = getchar()) != '\n') {
					if (ch < '0' || ch>'9') {
						printf("Wrong input\n");
						rewind(stdin);
						scanf_s("%d", &arr[i][j]);
					}
					while (sc == 0) {
						printf("Wrong input\n");
						rewind(stdin);
						sc = scanf_s("%d", &arr[i][j]);
					}


				}
			
		}
}
void Out_matrix(int** arr, int n, int m) {
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf(" %2d", arr[i][j]);
		printf("\n");
	}

}

void find_min_row(int** arr,int n,int m,int* min,int start) {
	int sum = 0;
	int sum_min = 0;
	for (int i = 0; i < m; i++)
		if (arr[start][i] % 2 == 0)
			sum_min += arr[start][i];
	*min = start;

	for (int i = start; i < n; i++) {
		for (int h = 0; h < m; h++)
			if (arr[i][h] % 2 == 0)
				sum += arr[i][h];
		if (sum < sum_min) {
			sum_min = sum;
			*min = i;
		}
		sum = 0;
	}
	
}
void merge_sort_rows(int** arr, int left, int right, int m,int n) {
	
	int min = 0;
	int mid = left + (right - left) / 2;
	int* temp=NULL;
	for (int i = 0; i < mid; i++) {
		find_min_row(arr, mid, m, &min, i);
		temp = arr[min];
		arr[min] = arr[i];
		arr[i] = temp;
	}
	for (int i = mid; i < right; i++) {
		find_min_row(arr, right, m, &min, i);
		temp = arr[min];
		arr[min] = arr[i];
		arr[i] = temp;
	}
	
			merge(arr, left, mid, right, m, n);
		
}

void merge(int** arr, int left, int mid, int right, int m,int n) {
	double_matrix(&arr, n);
	int it1 = 0, it2 = 0;
	int sum1 = 0, sum2 = 0;
	while (left + it1 < mid && mid + it2 < right) {

		for (int i = 0; i < m; i++)
			if (arr[left + it1][i] % 2 == 0)
				sum1 += arr[left + it1][i];

		for (int i = 0; i < m; i++)
			if (arr[mid + it2][i] % 2 == 0)
				sum2 += arr[mid + it2][i];

		if (sum1 < sum2) {
			arr[it1 + it2 + right] = arr[left + it1];
			it1++;
		}
		else {
			arr[it1 + it2 + right] = arr[mid + it2];
			it2++;
		}
		sum1 = 0; sum2 = 0;
	}
	while (left + it1 < mid) {
		arr[it1 + it2+right ] = arr[left + it1];
		it1++;
	}
	while (mid + it2 < right) {
		arr[it1 + it2+right ] = arr[mid + it2];
		it2++;
	}
	
	for (int i = 0; i <right; i++)
		arr[i] = arr[i+right];

	return_matrix(&arr, n);
	printf("The result is:\n");
	Out_matrix(arr, n, m);
	
}
void double_matrix(int*** arr, int n) {
	
	*arr = (int**)realloc(*arr,   (2*n) * sizeof(int*));
}
void return_matrix(int***arr, int n) {
	*arr = (int**)realloc(*arr,  n * sizeof(int*));
}