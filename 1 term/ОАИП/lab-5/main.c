#include "tasks.h"
int main() {
	int menu = 0;
	printf("Input:\n 1 - for task1\n 2 - for task2\n 3 - for task3\n 4 - to exit the programm\n");
	choose_menu(&menu);
	if (menu == 1) task1();
	if (menu == 2) task2();
	if (menu == 3) task3();
	if (menu == 4) {
		printf("Thanks for testing my program :D\n");
		return 0;
	}
	return 0;
}