#include <stdio.h>
int main() {
	float x, y, x1, y1, x2, y2;
	printf("Input the coordinates of the center point of the circle :\n");
	scanf_s("%f%f", &x, &y);
	printf("Input the coordinates of the point belongs to the circle :\n");
	scanf_s("%f%f", &x1, &y1);
	printf("Input the coordinates of the other point : \n");
	scanf_s("%f%f", &x2, &y2);
	if (((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y)) == ((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y)))
		printf("The point belongs to circle");
	else printf("The point doesn't belongs to circle");
	return 0;
}