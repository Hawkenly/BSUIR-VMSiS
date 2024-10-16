#include <stdio.h>
long int factorial(long int fact) {
	 /*int res = 1;
	 for (int i = 1; i <= fact; i++) {
		 res *= i;
	 }
	 return res;*/
		if (fact ==0 || fact ==1) return 1;
		if (fact > 0) return fact * factorial(fact - 1);
	}

 double stepen(double num,int k) {
	/* int res = 1;
	 for (int i = 1; i <= k; i++) {
		 res *= num;
	 }
	 return res;*/
		if (k == 0) return 1;
		if (k > 0) return num * stepen(num, k - 1);
}

 float inputfloat(float n) {
	 char ch;
	 while ((ch = getchar()) != '\n') {
		 if ((ch >= 48 && ch <= 57) || ch=='.' || ch=='-')
			 return 1;
		 else {
			 printf("Wrong input\n");
			 rewind(stdin);
			 scanf_s("%f", &n);
		 }

		 }
	 return n;
 }