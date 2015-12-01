
#include "ejercicio1.h"
#include "ejercicio2.h"

void ejercicio2_1(const std::string& number) {
	int x = intFromBinary(number);

	printf_s("Ejercicio2_1 (Base2 previo): %s\n", binaryFromInt(x).c_str());
	printf_s("Ejercicio2_1 (Base10 previo): %d\n", x);
	
	x = ~x;
	printf_s("Ejercicio2_1 (Base2 NOT): %s\n", binaryFromInt(x).c_str());
	printf_s("Ejercicio2_1 (Base10 NOT): %d\n", x);
}

void ejercicio2_2(const std::string& number) {
	int x = intFromBinary(number);

	printf_s("Ejercicio2_2 (<<1): %d\n", x << 1);
	printf_s("Ejercicio2_2 (<<3): %d\n", x << 3);
	printf_s("Ejercicio2_2 (<<6): %d\n", x << 6);
}

void ejercicio2_3() {
	int sInt = intFromBinary("11111111111111111111111111111111");
	unsigned int uInt = (unsigned int)(sInt);

	printf_s("Ejercicio2_3\n\n");
	printf_s("signed =%d\n", sInt);
	printf_s("unsigned = %u\n", uInt);

	//2.3.1
	sInt <<= 1;
	uInt <<= 1;

	printf_s("signed<<1 =%d\n", sInt);
	printf_s("unsigned<<1 = %u\n", uInt);

	sInt >>= 2;
	uInt >>= 2;

	printf_s("signed>>1 =%d\n", sInt);
	printf_s("unsigned>>1 = %u\n", uInt);

	//2.3.2
	sInt++;
	uInt--;

	printf_s("(signed<<1)++ =%d\n", sInt);
	printf_s("(unsigned<<1)-- = %d\n", uInt);

	//2.3.3
	int pink = 0xCC6699;

	printf_s("R = %d\n", (pink & 0xFF0000) >> 16);
	printf_s("G = %d\n", (pink & 0x00FF00) >> 8);
	printf_s("B = %d\n", (pink & 0x0000FF));
}