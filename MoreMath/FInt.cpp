#include "FInt.h"

FInt FMultiply(FInt x, FInt y)
{
	return x * (y >> 16);
}

FInt FDivide(FInt x, FInt y)
{
	return (x << 16) / y;
}
