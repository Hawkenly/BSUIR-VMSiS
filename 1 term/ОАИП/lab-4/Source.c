#include "Tasks.h"
int main() {
	int mchoose = 0;
	printf("Choose the task u want to open: 1 - first task, 2 - second task, 3 - third task, 4 - if u want to exit\n");
	choose_menu(&mchoose);
	if (mchoose == 1) task1();
	if (mchoose == 2) task2();
	if (mchoose == 3) task3();
	if (mchoose==4) printf("Thanks for testing my program :)");
	return 0;
}