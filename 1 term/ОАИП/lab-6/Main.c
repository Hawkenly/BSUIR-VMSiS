#include "Tasks.h"
int main() {
	int menu_choice = 0;
	printf("If u want to lauch 1st task input - 1\nIf u want to laucn 2nd task input - 2\nIf u want to close the program input - 3\n");
	menu(&menu_choice);
	if (menu_choice == 1) task1();
	if (menu_choice == 2) task2();
	if (menu_choice == 3) {
		printf("Thanks for testing my program :D\n");
		return 0;
	}

	return 0;
}