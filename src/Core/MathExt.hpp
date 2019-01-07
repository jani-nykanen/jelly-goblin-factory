// Some math extension functions
// (c) 2019 Jani Nykänen

#ifndef __MATH_EXT_H__
#define __MATH_EXT_H__

#include "Types.hpp"

#define MAX(type) inline type max_##type (type a, type b) {return a<b?b:a;}
MAX(uint8)
MAX(int16)
MAX(uint16)
MAX(int32)
MAX(uint32)

#define MIN(type) inline type min_##type (type a, type b) {return a>b?b:a;}
MIN(uint8)
MIN(int16)
MIN(uint16)
MIN(int32)
MIN(uint32)

// Negative modulo
int negMod(int m, int n);

// Fixed sine
int fixedSin(int angle);
// Fixed cosine
int fixedCos(int angle);

#endif // __MATH_EXT_H__
