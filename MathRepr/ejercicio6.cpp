
#include "ejercicio6.h"

void ejercicio6_1() {
	float point2 = 0.2f;
	printf("ejercicio6_1: %1.16f\n", point2);
}

void ejercicio6_2() {
	//se observa que no es exacto al tener una precisi�n finita, hay 7 bits que s�, pero a partir de ah� habr�a que seguir ajustando a�adiendo bits
}

void ejercicio6_4() {
	float f = 0.1f;
	float sum = 0;

	for (int i = 0; i < 100; ++i)
		sum += f;
	
	float product = f * 100;

	printf("ejercicio6_4(product): %f\n", product);
	printf("ejercicio6_4(sum): %f\n", sum);
}

void ejercicio6_5() {
	float f = 0.1f;
	float sum = 0;

	for (int i = 0; i < 100; ++i)
		sum += f;

	float product = f * 100;

	printf("ejercicio6_5(product): %1.15f\n", product);
	printf("ejercicio6_5(sum): %1.15f\n", sum);
}

void ejercicio6_6() {

}