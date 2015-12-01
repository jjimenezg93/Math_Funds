#pragma warning(disable: 4244)

#include "common.h"

int intFromBinary(const std::string& number) {
	int toRet = 0;
	for (unsigned short int i = 0; i < number.size(); i++) {
		toRet <<= 1;
		if (number.at(i) == '1')
			toRet++;
	}

	return toRet;
}

std::string binaryFromInt(int x) {
	std::string str = "";
	unsigned int z = intFromBinary("10000000000000000000000000000000");

	for (; z > 0; z >>= 1) {
		str = str + ((x & z) == z ? "1" : "0");
	}

	return str;
}

std::string binaryFromChar(char x) {
	std::string str = "";
	unsigned char z = intFromBinary("10000000");

	for (; z > 0; z >>= 1) {
		str = str + ((x & z) == z ? "1" : "0");
	}

	return str;
}

void printIntAsBinary(int x) {
	std::string str = binaryFromInt(x);
	printf("%s\n", str.c_str());
}