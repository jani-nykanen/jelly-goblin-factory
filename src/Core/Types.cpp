// Generic types
// (c) 2019 Jani Nykänen

#include "Types.hpp"

#include "MathExt.hpp"

#include <cmath>


// Matrix constructor
Matrix3::Matrix3() {

    identity();
}


// Multiply
Vector2 Matrix3::mul(Vector2 p) {

    Vector2 ret;

    ret.x = m11 * p.x + m21 * p.y + m31 * 1.0f;
    ret.y = m12 * p.x + m22 * p.y + m32 * 1.0f;

    return ret;
}
Matrix3 Matrix3::mul(Matrix3 M) {

    Matrix3 A;

    A.m11 = m11 * M.m11 + m21 * M.m12 + m31 * M.m13;
	A.m21 = m11 * M.m21 + m21 * M.m22 + m31 * M.m23;
	A.m31 = m11 * M.m31 + m21 * M.m32 + m31 * M.m33;

	A.m12 = m12 * M.m11 + m22 * M.m12 + m32 * M.m13;
	A.m22 = m12 * M.m21 + m22 * M.m22 + m32 * M.m23;
	A.m32 = m12 * M.m31 + m22 * M.m32 + m32 * M.m33;

	A.m13 = m13 * M.m11 + m23 * M.m12 + m33 * M.m13;
	A.m23 = m13 * M.m21 + m23 * M.m22 + m33 * M.m23;
	A.m33 = m13 * M.m31 + m23 * M.m32 + m33 * M.m33;

    return A;
}


// Set to identity matrix
Matrix3 Matrix3::identity() {

    m11 = 1.0f; m21 = 0; m31 = 0;
	m12 = 0; m22 = 1.0f; m32 = 0;
	m13 = 0; m23 = 0; m33 = 1.0f;

    return *this;
}


// Set to rotation matrix
Matrix3 Matrix3::rotate(float angle) {

    float s = (float)sin(angle);
    float c = (float)cos(angle);

	m11 = c; m21 =-s; m31 = 0;
	m12 = s; m22 = c; m32 = 0;
	m13 = 0; m23 = 0; m33 = 1.0f;

    return *this;
}


// Scale
Matrix3 Matrix3::scale(float x, float y) {

    m11 = x; m21 = 0; m31 = 0;
	m12 = 0; m22 = y; m32 = 0;
	m13 = 0; m23 = 0; m33 = 1.0f;

    return *this;
}


// Translate
Matrix3 Matrix3::translate(float x, float y) {

    m11 = 1.0f; m21 = 0; m31 = x;
	m12 = 0; m22 = 1.0f; m32 = y;
	m13 = 0; m23 = 0; m33 = 1.0f;

    return *this;
}


// Ortho 2D projection
Matrix3 Matrix3::ortho2D(float left, float right, 
        float bottom, float top) {

    float w = right - left;
	float h = top - bottom;

	m11 = 2.0f / w; m21 = 0; m31 = -(right+left)/w;
	m12 = 0; m22 = -2.0f / h; m32 = (top+bottom)/h;
	m13 = 0; m23 = 0; m33 = 1.0f;

    return *this;
}


// To array
float* Matrix3::toArray() {

    arr[0] = m11; arr[1] = m12; arr[2] = m13;
    arr[3] = m21; arr[4] = m22; arr[5] = m23;
    arr[6] = m31; arr[7] = m32; arr[8] = m33;

    return arr;
}
