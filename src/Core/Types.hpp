// Generic types
// (c) 2019 Jani Nykänen

#ifndef __TYPES_H__
#define __TYPES_H__

#define FIXED_PRECISION 256

// Primitive types
typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef signed long int64;
typedef unsigned long uint64;

// "Fixed point" number
typedef int FixedPoint;

// To int
inline int fixedToInt(FixedPoint fp) {
    return fp / FIXED_PRECISION;
}
// Float to fixed
inline FixedPoint floatToFixed(float f) {

    return (FixedPoint)(f * FIXED_PRECISION);
}


// Fixed point vector
struct Vec2Fixed {

    // Components
    int x, y;

    // Constructor
    inline Vec2Fixed(){x=0;y=0;}
    inline Vec2Fixed(int x, int y) {
        this->x=x*FIXED_PRECISION; 
        this->y=y*FIXED_PRECISION;
    };
    inline Vec2Fixed(float x, float y) {
        this->x=floatToFixed(x);
        this->y=floatToFixed(y);
    };

    // Get components
    inline int getXInt(){return x / FIXED_PRECISION;}
    inline int getYInt(){return y / FIXED_PRECISION;}
};



// Fixed point 3x3 matrix
struct Mat3Fixed {

    // Components
    int m11, m21, m31,
        m12, m22, m32,
        m13, m23, m33;

    // Constructor
    Mat3Fixed();

    // Set to the identity matrix
    void identity();

    // Multiply
    Vec2Fixed mul(Vec2Fixed p);
    Mat3Fixed mul(Mat3Fixed M);

    // Set to rotation matrix
    Mat3Fixed rotate(int angle);
    // Scale
    Mat3Fixed scale(FixedPoint x, FixedPoint y);
    // Translate
    Mat3Fixed translate(FixedPoint x, FixedPoint y);

    // Inverse
    Mat3Fixed inverse();
};

#endif // __TYPES_H__
 