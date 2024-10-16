#include <stdio.h>
#include "Header.h"
int inputint(int n);
int main() {
	int sum = 0, i, j,  m,  arr[3][11];
	// Ввод и проверка
	printf("Input m rubles :\n");
    scanf_s("%d", &m);
	m=inputint(m);
	while (m < 10 || m>50) {
		printf("Wrong input\n");
		rewind(stdin);
		 scanf_s("%d", &m);
		 m=inputint(m);
	}
	//Заполняем массив возможными комбинациями чисел (рублей)
	for (i=0; i <= 2; i++)
		for (j = 0; j <= 10; j++)
			arr[i][j] = j*(2*i+1);
	//Проверяем сумму 3х чисел в каждой строчке
	for (i = 0; i <= 10; i++) {
		for (j = 0; j <= 10; j++) {
			for (int k = 0; k <= 10; k++) {
				sum = arr[0][i] + arr[1][j] + arr[2][k];
				if ((sum == m) && (i + j + k == 10)) {
					printf("Possible"); return 0;
				}
			}
		}
	}
	printf("Impossible");
	return 0;
}
