#include <stdio.h>
void function(double v1, double v2, double s, double vsh, double s0) {
	double v1sh = v1 + vsh/*относительная скорость шмеля и 1го */, dt1/* время полета шмеля до 2го */ , ds1/*расстояние  2го*/;
	double v2sh = v2 + vsh /*относительная скорость шмеля и 2го */ , dt2/* время полета шмеля до 1го */, ds2/*расстояние  1го*/,ssh/*расстояние полета шмеля*/;
	while (s > s0) {
		dt1 = s / v2sh;
		ssh = dt1 * vsh;
		ds1 = dt1 * v1;
		ds2 = dt1 * v2;
		s -= ds1 + ds2;
		printf("%f\n", ssh);
		dt2 = s / v1sh;
		ds1 = dt2 * v1;
		ds2 = dt2 * v2;
		ssh = dt2 * vsh;
		printf("%f\n", ssh);
		s -= ds1 + ds2;
	}
}
	