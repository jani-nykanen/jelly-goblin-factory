// Generic types
// (c) 2019 Jani Nykänen

#include "Types.hpp"

#include <cmath>


// Constructor
Mat3Fixed::Mat3Fixed() {

    identity();
}


// Constructor
void Mat3Fixed::identity() {

    m11 = FIXED_PRECISION; m21 = 0; m31 = 0;
	m12 = 0; m22 = FIXED_PRECISION; m32 = 0;
	m13 = 0; m23 = 0; m33 = FIXED_PRECISION;
}


// Multiply
Vec2Fixed Mat3Fixed::mul(Vec2Fixed p) {

    Vec2Fixed ret;

    ret.x = m11 * p.x + m21 * p.y + m31 * FIXED_PRECISION;
    ret.y = m12 * p.x + m22 * p.y + m32 * FIXED_PRECISION;

    ret.x /= FIXED_PRECISION;
    ret.y /= FIXED_PRECISION;

    return ret;
}
Mat3Fixed Mat3Fixed::mul(Mat3Fixed M) {

    Mat3Fixed A;

    A.m11 = m11 * M.m11 + m21 * M.m12 + m31 * M.m13;
	A.m21 = m11 * M.m21 + m21 * M.m22 + m31 * M.m23;
	A.m31 = m11 * M.m31 + m21 * M.m32 + m31 * M.m33;

	A.m12 = m12 * M.m11 + m22 * M.m12 + m32 * M.m13;
	A.m22 = m12 * M.m21 + m22 * M.m22 + m32 * M.m23;
	A.m32 = m12 * M.m31 + m22 * M.m32 + m32 * M.m33;

	A.m13 = m13 * M.m11 + m23 * M.m12 + m33 * M.m13;
	A.m23 = m13 * M.m21 + m23 * M.m22 + m33 * M.m23;
	A.m33 = m13 * M.m31 + m23 * M.m32 + m33 * M.m33;

    A.m11 /= FIXED_PRECISION; A.m12 /= FIXED_PRECISION; A.m13 /= FIXED_PRECISION;
    A.m21 /= FIXED_PRECISION; A.m22 /= FIXED_PRECISION; A.m23 /= FIXED_PRECISION;
    A.m31 /= FIXED_PRECISION; A.m32 /= FIXED_PRECISION; A.m33 /= FIXED_PRECISION;

    return A;
}


// Set to rotation matrix
Mat3Fixed Mat3Fixed::rotate(int angle) {

    FixedPoint c = floatToFixed(cosf(angle / 180.0f * M_PI));
	FixedPoint s = floatToFixed(sinf(angle / 180.0f * M_PI));

	m11 = c; m21 =-s; m31 = 0;
	m12 = s; m22 = c; m32 = 0;
	m13 = 0; m23 = 0; m33 = FIXED_PRECISION;

    return *this;
}


// Scale
Mat3Fixed Mat3Fixed::scale(FixedPoint x, FixedPoint y) {

    m11 = x; m21 = 0; m31 = 0;
	m12 = 0; m22 = y; m32 = 0;
	m13 = 0; m23 = 0; m33 = FIXED_PRECISION;

    return *this;
}


// Translate
Mat3Fixed Mat3Fixed::translate(FixedPoint x, FixedPoint y) {

    m11 = FIXED_PRECISION; m21 = 0; m31 = x;
	m12 = 0; m22 = FIXED_PRECISION; m32 = y;
	m13 = 0; m23 = 0; m33 = FIXED_PRECISION;

    return *this;
}


// Inverse
Mat3Fixed Mat3Fixed::inverse() {

    Mat3Fixed A;
    // TODO: THIS!
    return A;
}
