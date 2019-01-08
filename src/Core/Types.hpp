// Generic types
// (c) 2019 Jani Nykänen

#ifndef __TYPES_H__
#define __TYPES_H__

// Primitive types
typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef signed long int64;
typedef unsigned long uint64;


// Fixed point vector
struct Vector2 {

    // Components
    float x, y;

    // Constructor
    inline Vector2(){x=0;y=0;}
    inline Vector2(float x, float y) {

        this->x = x;
        this->y = y;
    };
};

// Color
struct Color {
    float r,g,b,a;
    inline Color(float r=1, float g=1, float b=1, float a=1) {

        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

// Fixed point 3x3 matrix
class Matrix3 {

private:

    // Components
    float m11, m21, m31,
        m12, m22, m32,
        m13, m23, m33;
    float arr[3*3];

public:

    // Constructor
    Matrix3();

    // Multiply
    Vector2 mul(Vector2 p);
    Matrix3 mul(Matrix3 M);

    // Set to the identity matrix
    Matrix3 identity();
    // Set to rotation matrix
    Matrix3 rotate(float angle);
    // Scale
    Matrix3 scale(float x, float y);
    // Translate
    Matrix3 translate(float x, float y);
    // Ortho 2D projection
    Matrix3 ortho2D(float left, float right, 
        float bottom, float top);

    // To array
    float* toArray();
};

#endif // __TYPES_H__
 