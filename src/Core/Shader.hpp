// Shader
// (c) 2019 Jani Nykänen

#ifndef __SHADER_H__
#define __SHADER_H__

#include "Types.hpp"

#include <string>

// Shader type
class Shader {

private:

    // Program ID
    uint32 program;

    // Uniforms
    uint32 unifPos;
    uint32 unifSize;

    // Build shader
    void build(std::string vertex, 
        std::string fragment);

public:

    // Constructors
    Shader(std::string vertex, 
        std::string fragment);
    Shader();
    // Destructor
    ~Shader();

    // Use shader
    void useShader();
    // Set uniforms
    void setUniforms(float x, float y, float w, float h);
};


#endif // __SHADER_H__
