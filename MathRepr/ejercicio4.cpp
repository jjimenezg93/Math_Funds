
#include "ejercicio4.h"

void ejercicio4() {
	float mod = 456 % 1;
	printf_s("456 mod 1 = %f\n", mod);
	mod = 456 % 10;
	printf_s("456 mod 10 = %f\n", mod);
	mod = 456 % 1000;
	printf_s("456 mod 1000 = %f\n", mod);
}

void ejercicio4_1() {
	float f;
	for (int i = 0; i <= 10; i++) {
		f = static_cast<float>(float(i % 2));
		printf_s("i mod 2 = %f\n", f);
	}
}