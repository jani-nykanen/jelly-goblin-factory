// Transformations manager
// (c) 2019 Jani Nykänen

#ifndef __TRANSFORMATIONS_H__
#define __TRANSFORMATIONS_H__

#include "Types.hpp"
#include "Shader.hpp"

#include <vector>
#include <stack>

// Transformations class
class Transformations {

private:

    // Viewport
    Vector2 viewport;

    // Matrices
    Matrix3 view;
    Matrix3 model;
    Matrix3 operand;

    // Model stack
    std::stack<Matrix3> stack;

protected:

    // Framebuffer size
    Vector2 fbSize;

    // Pass transformations to shader
    void passToShader(Shader* s);

public:

    // Constructor
    Transformations();

    // Transformations
    void identity();
    void translate(float x, float y);
    void scale(float x, float y);
    void rotate(float angle);

    // Set view
    void setView(float w, float h);
    void setView(float h);

    // Stack operations
    void push();
    void pop();
    inline void resetStack() { stack.empty(); }

    // Getters
    inline Vector2 getViewport() {return viewport;}

};

#endif // __TRANSFORMATIONS_H__
