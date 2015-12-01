
#include "ejercicio5.h"
#pragma warning(disable: 4310)

void ejercicio5_1() {
	int a = 4;
	int b = -4;
	int sum = a + b;
	printf_s("sum(a + b) = %d\n", sum);
}

void ejercicio5_2() {
	int a = 4;
	int b = -4;
	int sum = a + b;
	printf_s("Ejercicio5_2(a): %s\n", binaryFromInt(a).c_str());
	printf_s("Ejercicio5_2(b): %s\n", binaryFromInt(b).c_str());
	printf_s("Ejercicio5_2(sum): %s\n", binaryFromInt(sum).c_str());
	//lo que ocurre es una suma bit a bit normal:
	//a :	00000000000000000000000000000100
	//b :	11111111111111111111111111111100
	//sum :	00000000000000000000000000000000
	//de derecha a izquierda, cuando hay 1 + 1 = 0 y se lleva acarreo, y el acarreo se arrastra hasta la izquierda de todo y queda fuera
}

void ejercicio5_3() {
#pragma warning(disable: 4310)
	char c = (char)255;
	printf_s("Ejercicio5_3(c): %s\n", binaryFromChar(c).c_str());
#pragma warning(default: 4310)
}

void ejercicio5_4() {
	char c = (char)255;
	printf_s("Ejercicio5_4(c): %s\n", binaryFromChar(c).c_str());

	unsigned char uc = (unsigned char)255;
	printf_s("Ejercicio5_4(uc): %s\n", binaryFromChar(uc).c_str());
}

void ejercicio5_5() {
	//c tiene bit de signo, por lo que su rango es con 7 bits, de -128 < c < 127, entonces al interpretarlo como un int, es -1, aunque su binario sea igual que el de uc
	char c = (char)255;
	printf_s("Ejercicio5_5(c): %d\n", c);

	//en el caso de uc, como es unsigned tiene rango 0 < uc < 255
	unsigned char uc = (unsigned char)255;
	printf_s("Ejercicio5_5(uc): %d\n", uc);
}

void ejercicio5_6() {
	char d = (char)128; // only to 127
	printf_s("Ejercicio5_6(d): %s\n", binaryFromChar(d).c_str());
	//aquí d = 10000000 (que también es = e), se produce desbordamiento al ser 127 el límite de los unsigned

	char e = (char)-128;
	printf_s("Ejercicio5_6(e): %s\n", binaryFromChar(e).c_str());
}

void ejercicio5_7() {
	//
}