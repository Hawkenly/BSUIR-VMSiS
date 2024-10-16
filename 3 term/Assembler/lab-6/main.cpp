#include <iostream>
#include <limits>
#pragma inline

#define SIZE 10
float mas[SIZE];

void asmFunc();
void OutputArr();
void InputArr();

int main() {
	InputArr();
	OutputArr();
	std::cout << std::endl;
	asmFunc();

	OutputArr();

	return 0;
}

void asmFunc() {
	__asm {
		finit
		lea ebx, mas
		mov ecx, 10

		func:
		fld[ebx]
			fsin
			fstp[ebx]

			add ebx, 4
			loop func

			fwait

	}

}
void OutputArr() {
	std::cout << "Your massive: " << std::endl;
	for (int i = 0; i < SIZE; i++)
		std::cout << mas[i]<<' ';
}

void InputArr() {
	std::cout << "Input elements of array: " << std::endl;
	for (int i = 0; i < SIZE; i++) {
		std::cin >> mas[i];
		while (!std::cin) {
			std::cout << "Incorrect input." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> mas[i];
		}


	}
}