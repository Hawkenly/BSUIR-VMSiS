#include <stdio.h>
#include <stdlib.h>

void choose_menu(int* menu);

//For the first task
void memory_array(float** arr, int*n);
void fill_array(float* arr, int* n);
void output_array(float* arr, int* n);
void delete_integer(float* arr, int* n);
void free_array(float* arr);

//For the second task
void memory_matrix(int*** matrix, int *N, int* M);
void input_matrix(int** matrix, int* N, int* M);
void delete_elements(int** matrix, int* N, int* M);
void output_matrix(int** matrix, int* N, int* M);
void free_matrix(int** matrix, int* N);

//For the third task
void memory_non_matrix(int*** mas, int* N);
void input_non_matrix(int** mas, int* i, int* col);
void double_odd_element(int** mas, int N);
void plus_memory(int*** mas, int more, int i);
void output_non_matrix(int** mas, int N);
void free_non_matrix(int** mas, int N);

void choose_menu(int* menu) {
	scanf_s("%d", menu);
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch < '1' || ch>'4') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", menu);
		}
	}
	if (*menu < 1 || *menu>4) {
		printf("Wrong input\n");
		choose_menu(menu);
	}
}
void memory_array(float** arr,int *n) {
	scanf_s("%d", n);
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch < '0' || ch>'9') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", n);
		}
	}
	if (*n <= 0) {
		printf("Wrong input\n");
		memory_array(arr, n);
	}
	*arr = (float*)calloc(*n, sizeof(float));
}

void fill_array(float* arr, int* n) {
	int sc = 0;
	for (int i = 0; i < *n; i++) {
		printf("Input the [%d] element of the array\n", i);
		sc = scanf_s("%f", &arr[i]);
		while (sc == 0) {
			printf("Wrong input\n");
			rewind(stdin);
			sc = scanf_s("%f", &arr[i]);
		}
		
		char ch;
		while ((ch = getchar()) != '\n') {
			if (ch < '0' || ch>'9') {
				printf("Wrong input\n");
				rewind(stdin);
				scanf_s("%f", &arr[i]);
			}
		}
	}

}

void output_array(float* arr, int* n) {
	for (int i = 0; i < *n; i++)
		printf("%.3f ", arr[i]);
}
void delete_integer(float* arr, int* n) {
	for (int i = 0; i < *n; i++) {
		if ((int)arr[i] == arr[i]) {
			for (int j = i + 1; j < *n;j++) {
				arr[j-1] = arr[j];
			}
			(*n)--;
			i--;
		}
	}
}

void free_array(float* arr) {
	free(arr);
}

void memory_matrix(int*** matrix, int* N, int* M) {
	scanf_s("%d", N);
	scanf_s("%d", M);
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch < '0' || ch>'9') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", N);
			scanf_s("%d", M);
		}
	}
	if (*N <= 0 || *M <= 0) {
		printf("Wrong input\n");
		memory_matrix(matrix, N, M);
	}
	*matrix = (int**)calloc(*N, sizeof(int*));
	for (int i = 0; i < *N; i++)
		(*matrix)[i] = (int*)calloc(*M, sizeof(int));
	 
}

void input_matrix(int** matrix, int* N, int* M) {
	for (int i = 0; i < *N; i++)
		for (int j = 0; j < *M; j++) {
			printf("Input the element [%d][%d]\t", i, j);
			int sc=scanf_s("%d", &matrix[i][j]);
			while (sc == 0) {
				printf("Wrong input\n");
				rewind(stdin);
				sc=scanf_s("%d", &matrix[i][j]);
			}
			char ch;
			while ((ch = getchar()) != '\n') {
				if (ch < '0' || ch>'9') {
					printf("Wrong input\n");
					rewind(stdin);
					scanf_s("%d", &matrix[i][j]);
				}
			}
		}
}
void delete_elements(int** matrix, int* N, int* M) {
	int i = *N - 1; int j = 0;
		while(i>=0 || j<*M){
			for (int h = j; h < *M - 1; h++)
				matrix[i][h] = matrix[i][h + 1];
			i--;
			j++;
	}
		(*M)--;
}

void output_matrix(int** matrix, int* N, int* M) {
	for (int i = 0; i < *N; i++) {
		for (int j = 0; j < *M; j++)
			printf("%3d", matrix[i][j]);
		printf("\n");
	}
}

void free_matrix(int** matrix, int* N) {
	for (int i = 0; i < *N; i++)
		free(matrix[i]);
	free(matrix);


}

void memory_non_matrix(int*** mas, int* N) {
	int i = 0;
	int col = 0;

	int sc = scanf_s("%d", N);
	while (sc == 0) {
		printf("Wrong input\n");
		rewind(stdin);
		sc = scanf_s("%d", N);
	}
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch < '0' || ch>'9') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", N);
		}
	}
	if (*N <= 0) {
		printf("Wrong input\n");
		memory_non_matrix(mas, N);
	}

	
	*mas = (int**)calloc(*N, sizeof(int*));
	printf("If u want to stop input this line input -100\n");
	for (i; i < *N; ) {
		(*mas)[i] = (int*)realloc((*mas)[i], (col + 1) * sizeof(int));
		input_non_matrix(*mas, &i, &col);
	}
}

void input_non_matrix(int** mas, int *i,int *col) {
	printf("Input the element [%d][%d] of the array\n", *i, *col);

	int sc=scanf_s("%d", &mas[*i][*col]);
	while (sc == 0) {
		printf("Wrong input\n");
		rewind(stdin);
		sc = scanf_s("%d", &mas[*i][*col]);
	}
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch < '0' || ch>'9') {
			printf("Wrong input\n");
			rewind(stdin);
			scanf_s("%d", &mas[*i][*col]);
		}
	}

	if (mas[*i][*col] == -100) {
		(*i)++;
		(*col) = 0;
	}
	else (*col)++;
}

void double_odd_element(int** mas, int N) {
	int col;
	for (int i = 1; i < N; i += 2) {
		col = 1;
		for (int j = 0; mas[i][j] != -100; j++)
			col++;
		for(int k=0;k<col;k++)
			if ( mas[i][k] % 2 == 1) {
				int more = col + 1;
				plus_memory(&mas, more, i);
				for (int h = col-1; h >= k; h--)
					 mas[i][h + 1] = mas[i][h];
				col = more;
				k++;
		}
	}
}
void plus_memory(int*** mas,int more,int i) {
	(*mas)[i] = (int*)realloc((*mas)[i], more * sizeof(int));
}

void output_non_matrix(int** mas, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; mas[i][j] != -100; j++)
			printf("%3d", mas[i][j]);
		printf("\n");
	}
}

void free_non_matrix(int** mas, int N) {
	for (int i = 0; i < N; i++) 
		free(mas[i]);
	free(mas);
}