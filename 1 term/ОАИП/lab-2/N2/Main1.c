#include <stdio.h>
#include "Header1.h"
void function(double v1, double v2, double s, double vsh, double s0);
int main() {
	double v1 = 2 , v2 = 3, vsh  = 5/*скорость шмеля */, s = 20;
	double s0 = 0.00001;   
	function(v1, v2, s, vsh, s0);
	return 0;
}
