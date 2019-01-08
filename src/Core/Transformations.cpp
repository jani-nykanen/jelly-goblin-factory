// Transformations manager
// (c) 2019 Jani Nykänen

#include "Transformations.hpp"


// Constructor
Transformations::Transformations() {

    model = Matrix3();
    view = Matrix3();
    operand = Matrix3();

    viewport = Vector2(1, 1);
    fbSize = Vector2(1, 1);
}


// Transformations
void Transformations::identity() {

    model.identity();
}
void Transformations::translate(float x, float y) {
    
    operand.translate(x, y);
    model = model.mul(operand);
}
void Transformations::scale(float x, float y) {

    operand.scale(x, y);
    model = model.mul(operand);
}
void Transformations::rotate(float angle) {
    
    operand.rotate(angle);
    model = model.mul(operand);
}


// Stack operations
void Transformations::push() {

    stack.push(model);
}
void Transformations::pop() {

    model = stack.top();
    stack.pop();
}
