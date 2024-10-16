#include "Header.h"
//Задача 1
int task1(){
float arr[100], abs[100];
float max=0, sum = 0;
int choose = 0, n = 0, num = 0;
printf("Choose how to fill the array:\n 1 - Keyboard input\n 2 - Random values\n 3 - If you want to close this program \n ");
input_choose(&choose);
if (choose == 1) keyboard_input(&n, arr);
if (choose == 2) random_input(&n, arr);
if (choose == 3) main();
for (int i = 0; i < n; i++)
	abs[i] = arr[i];
//Модуль элементов
for (int i = 0; i < n; i++) {
	if (abs[i] < 0) {
		abs[i] = 0 - abs[i];
	}
}
max = abs[0];
//Поиск максимального элемента
for (int i = 0; i < n; i++) {
	if (abs[i] > max) {
		max = abs[i];
		num = i;
	}
}
//Сумма элементов после первого положительного
for (int i = 0; i < n; i++) {
	if (arr[i] > 0) {
		for (int j = i + 1; j < n; j++) {
			sum += arr[j];
		}
		break;
	}
}
printf("The num of the max element is : %d\n", num);
printf("The sum of the elements after the first plus element is %.3f\n", sum);
return 0;
}
// Задача 2
int task2() {
	float arr[100];
	int n = 0, fl = 0;
	int k; int choose = 0;
	printf("Choose how to fill the array:\n 1 - Keyboard input\n 2 - Random values\n 3 - If you want to close this program \n ");
	input_choose(&choose);
	if (choose == 1) keyboard_input(&n, arr);
	if (choose == 2) random_input(&n, arr);
	if (choose == 3) main();

	inputint(&k,&fl);
	//Удалние каждого k-го элемента массива
	for (int i = k - 1; i < n;) {
		if (fl == 1) break;
		for (int j = i; j < n - 1; j++)
			arr[j] = arr[j + 1];
		n--;
		i = i + (k - 1);
	}
	for (int i = 0; i < n; i++)
		printf("%.3f " , arr[i]);
	return 0;
}
//Задача 3
int task3() {
	int length1 = 0,length2=0,length=0,choose=0,fl=0;
	int transfer = 0, nonzero = 0, col = 0;;
	char num1s[100],num2s[100];
	int num1[100], num2[100],result[100],temp[100];
	int check0=0;
	printf("Choose how to fill the array:\n 1 - Keyboard input\n 2 - Random values\n 3 - If you want to close this program \n ");
	input_choose(&choose);
	if (choose == 1) keyboard_input3(num1s, num2s, num1, num2, &length, &length1, &length2);
	if (choose == 2) random_input3(num1, num2,&length);
	if (choose == 3) main();
	for (int i = 0; i < length; i++) {//Проверка на равенство чисел
		if (num1[i] == num2[i]) { //Сравнение чисел исходя из элементов
			col++;
			continue;
		}
		if (num1[i] < num2[i]) { //Сравнение чисел по элементам и замена местами
			for (int i = 0; i < length; i++) {
				temp[i] = num1[i];
				num1[i] = num2[i];
				num2[i] = temp[i];
			}
			fl = 1;
		}
		break;
	}
	for (int j = length; j > 0; j--) {
		if (num1[j - 1] < num2[j - 1]) {
			transfer++;
			while (num1[j - 1 - transfer] == 0)
				transfer++;
			num1[j - 1 - transfer]--;
			transfer--;
			if (transfer == 0) {
				num1[j - 1] += 10;
			}
			else {
				while (transfer != 0) {
					num1[j - 1 - transfer] += 9;
					transfer--;
				}
				num1[j - 1] += 10;
			}

		}
		result[j - 1] = num1[j - 1] - num2[j - 1];
	}
	if (col == length ) {
		printf("The difference between the first and the second numbers is 0");
		return 0;
	}
	// Добавление минуса перед числом
	if (fl == 1) {
		for (int i = 0; i < length; i++)
			if (result[i] != 0) {
				result[i] = 0-result[i];
				break;
			}
	}
// Поиск первого ненулевого элемента
	for (int i = 0; i < length; i++) {
		if (result[i] != 0) {
			nonzero = result[i];
			break;
		}
	}
	//Удаление всех нулей до первого ненулевого элемента
	for (int i = 0; result[i] != nonzero; i++) {
		for (int j = i; j < length - 1; j++)
			result[j] = result[j + 1];
		length--; i--;
	}
	printf("The difference between the first and the second numbers is:\n");
	for (int i = 0; i < length; i++)
		printf("%d", result[i]);
	return 0;
}
		