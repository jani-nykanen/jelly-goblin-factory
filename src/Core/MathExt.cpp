// Some math extension functions
// (c) 2019 Jani Nykänen

#include "MathExt.hpp"

#include "Trig.cc"


// Negative modulo
int negMod(int m, int n) {

    if(m < 0) {

        return n - (-m % n);
    }
    return m % n;
}


// Fixed sine
int fixedSin(int angle) {

    return FIXED_SINE[negMod(angle, 360)];
}


// Fixed cosine
int fixedCos(int angle) {

    return FIXED_SINE[negMod(angle+90, 360)];
}

