#include<stdio.h>
int main() {
	int arr[100];
	int n;
	int k;
	printf("Input the number of elements of the array :\n");
	scanf_s("%d", &n);
	printf("Input k:\n");
	scanf_s("%d", &k);
	for (int i = 0; i < n; i++) {
		printf("Input the %d element of the array :\n", i);
		scanf_s("%d", &arr[i]);
	}
	for (int i = k-1; i <n;) {
			for (int j = i; j < n-1 ; j++)
				arr[j] = arr[j + 1];
			n--;
			i = i + (k - 1);
	
	}
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	return 0;
}