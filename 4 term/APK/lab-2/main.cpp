#include <dos.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct Symbol
{
	unsigned char code;
	unsigned char attribute;
}typedef Symbol;

unsigned char programAttribute = 0x0B;

void print(void)
{
	char temp;
	int i, val;
	Symbol far* screen = (Symbol far*)MK_FP(0xB800, 0);

	val = inp(0x21);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;  // shift right
		screen->code = temp + '0';
		screen->attribute = programAttribute;
		screen++;
	}
	screen++;

	val = inp(0xA1);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->code = temp + '0';
		screen->attribute = programAttribute;
		screen++;
	}
	screen += 63;

	outp(0x20, 0x0A);
	val = inp(0x20);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->code = temp + '0';
		screen->attribute = programAttribute;
		screen++;
	}
	screen++;
	outp(0xA0, 0x0A);

	val = inp(0xA0);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->code = temp + '0';
		screen->attribute = programAttribute;
		screen++;
	}
	screen += 63;
	outp(0x20, 0x0B);

	val = inp(0x20);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->code = temp + '0';
		screen->attribute = programAttribute;
		screen++;
	}
	screen++;
	outp(0xA0, 0x0B);

	val = inp(0xA0);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->code = temp + '0';
		screen->attribute = programAttribute;
		screen++;
	}
}
//IRQ 0-7
void interrupt(*oldInterrupt08) (void);
void interrupt(*oldInterrupt09) (void);
void interrupt(*oldInterrupt0A) (void);
void interrupt(*oldInterrupt0B) (void);
void interrupt(*oldInterrupt0C) (void);
void interrupt(*oldInterrupt0D) (void);
void interrupt(*oldInterrupt0E) (void);
void interrupt(*oldInterrupt0F) (void);

//IRQ 8-15
void interrupt(*oldInterrupt70) (void);
void interrupt(*oldInterrupt71) (void);
void interrupt(*oldInterrupt72) (void);
void interrupt(*oldInterrupt73) (void);
void interrupt(*oldInterrupt74) (void);
void interrupt(*oldInterrupt75) (void);
void interrupt(*oldInterrupt76) (void);
void interrupt(*oldInterrupt77) (void);



void interrupt  newInterruptB0(void) { print(); oldInterrupt08(); }
void interrupt  newInterruptB1(void) { print(); oldInterrupt09(); }
void interrupt  newInterruptB2(void) { print(); oldInterrupt0A(); }
void interrupt  newInterruptB3(void) { print(); oldInterrupt0B(); }
void interrupt  newInterruptB4(void) { print(); oldInterrupt0C(); }
void interrupt  newInterruptB5(void) { print(); oldInterrupt0D(); }
void interrupt  newInterruptB6(void) { print(); oldInterrupt0E(); }
void interrupt  newInterruptB7(void) { print(); oldInterrupt0F(); }

void interrupt  newInterrupt08(void) { print(); oldInterrupt70(); }
void interrupt  newInterrupt09(void) { print(); oldInterrupt71(); }
void interrupt  newInterrupt0A(void) { print(); oldInterrupt72(); }
void interrupt  newInterrupt0B(void) { print(); oldInterrupt73(); }
void interrupt  newInterrupt0C(void) { print(); oldInterrupt74(); }
void interrupt  newInterrupt0D(void) { print(); oldInterrupt75(); }
void interrupt  newInterrupt0E(void) { print(); oldInterrupt76(); }
void interrupt  newInterrupt0F(void) { print(); oldInterrupt77(); }

void initialize(void)
{
	oldInterrupt08 = getvect(0x08);
	oldInterrupt09 = getvect(0x09);
	oldInterrupt0A = getvect(0x0A);
	oldInterrupt0B = getvect(0x0B);
	oldInterrupt0C = getvect(0x0C);
	oldInterrupt0D = getvect(0x0D);
	oldInterrupt0E = getvect(0x0E);
	oldInterrupt0F = getvect(0x0F);

	oldInterrupt70 = getvect(0x70);
	oldInterrupt71 = getvect(0x71);
	oldInterrupt72 = getvect(0x72);
	oldInterrupt73 = getvect(0x73);
	oldInterrupt74 = getvect(0x74);
	oldInterrupt75 = getvect(0x75);
	oldInterrupt76 = getvect(0x76);
	oldInterrupt77 = getvect(0x77);


	setvect(0xB0, newInterruptB0);
	setvect(0xB1, newInterruptB1);
	setvect(0xB2, newInterruptB2);
	setvect(0xB3, newInterruptB3);
	setvect(0xB4, newInterruptB4);
	setvect(0xB5, newInterruptB5);
	setvect(0xB6, newInterruptB6);
	setvect(0xB7, newInterruptB7);

	setvect(0x08, newInterrupt08);
	setvect(0x09, newInterrupt09);
	setvect(0x0A, newInterrupt0A);
	setvect(0x0B, newInterrupt0B);
	setvect(0x0C, newInterrupt0C);
	setvect(0x0D, newInterrupt0D);
	setvect(0x0E, newInterrupt0E);
	setvect(0x0F, newInterrupt0F);

	_disable();

	outp(0x20, 0x11);
	outp(0x21, 0xB0);
	outp(0x21, 0x04);
	outp(0x21, 0x01);


	outp(0xA0, 0x11);
	outp(0xA1, 0x08);
	outp(0xA1, 0x02);
	outp(0xA1, 0x01);

	_enable();
}

int main()
{
	unsigned far* fp;
	initialize();
	system("cls");

	printf("                   - mask\n");
	printf("                   - prepare\n");
	printf("                   - service\n");
	printf("Master   Slave\n");

	FP_SEG(fp) = _psp;
	FP_OFF(fp) = 0x2c;
	_dos_freemem(*fp);

	_dos_keep(0, (_DS - _CS) + (_SP / 16) + 1);
	return 0;
}