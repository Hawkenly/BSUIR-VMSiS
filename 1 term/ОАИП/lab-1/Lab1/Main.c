
#include <stdio.h>
#include <math.h>
int main() {
	float S, h, a;
	float i=1.732;
	printf("Input the side of an equilateral triangle :\n");
	scanf_s("%f", &a);
	h = a * i / 2;
	S = a * a * i / 4;
	printf("The height of the triangle is = %.3f\nThe square of the triangle is = %.3f\n", h,S);
	return 0;
}

