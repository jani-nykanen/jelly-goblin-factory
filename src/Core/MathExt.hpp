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

#endif // __MATH_EXT_H__
