#include"Tasks.h"
int main() {
	int choose_menu=0;
	printf("Choose the program you want to open :\n 1 - The first program\n 2 - The second program\n 3 - The third program\n 4 - If you want to exit\n");
	menu_choose(&choose_menu);
	if (choose_menu == 1) task1(); //����� ������������ ������� �� ������8 � ����� ��������� ����� 1�� ��������������
	if (choose_menu == 2) task2(); //������� ������ k-� �������
	if (choose_menu == 3) task3(); //�������� 30-������� �����
	if (choose_menu == 4) {
		printf("Thanks, for testing my program ;)");
		return 0;
	}
	return 0;
}