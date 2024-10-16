#include <stdio.h>
#include "Header2.h"
float inputfloat(float n);
long int factorial(long int fact);
double  stepen(double num, int k);
int main() {
	const float pi = 3.1415;
	float X;
	float rad, Sum_sin = 0.0, Sum_cos = 0.0, ctg = 0.0;
	//Ввод и проверка на ввод
	printf("Input the angle in degrees ( angle should be between [-106;106] degrees, because after these values there are an error in the answer) : \n");
	scanf_s("%f", &X);
	X=inputfloat(X);
	//Перевод в радианы
	rad = X* pi / 180.0;
	//Разложение синуса и косинуса угла по ряду Тейлора на 10 членов
	for (int k = 0; k< 10; k++) {
		Sum_sin = Sum_sin + ((stepen(-1.0, k) * stepen(rad, 2 * k + 1)) / factorial(2 * k + 1));
		Sum_cos = Sum_cos + (( stepen(-1.0, k) * stepen(rad, 2 * k)) / factorial(2 * k)) ;
	}
	ctg = Sum_cos / Sum_sin;
	printf("ctg(X) = %.3f", Sum_cos);
	return 0;
}