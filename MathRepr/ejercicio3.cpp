#pragma warning(disable: 4189)

#include "ejercicio3.h"

void ejercicio3_1() {
	printf_s("sqrt(-1) = %f\n", sqrt(-1));
	//devuelve NaN
}

void ejercicio3_2() {
	int x = 0;
	int y = 0;
	//printf_s("0/0 = %d\n", x / y);	//excepcion de division por 0
	
	//printf_s("0/0 = %d\n", 0 / 0);
	//no deja compilar "error C2124: divide or mod by zero"
}

void ejercicio3_3() {
	float x = 1.0f;
	float y = 0.0f;
	//printf_s("1.0f / 0.0f = %d\n", x / y);	//excepcion de division por 0

	//printf_s("1.0f / 0.0f = %d\n", 1.0f / 0.0f);
	//no deja compilar "error C2124: divide or mod by zero"
}