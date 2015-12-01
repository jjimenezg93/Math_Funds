#ifndef _COMMON_H
#define _COMMON_H

#include <string>

int intFromBinary(const std::string& number);

std::string binaryFromInt(int x);

std::string binaryFromChar(char x);

void printIntAsBinary(int x);

#endif