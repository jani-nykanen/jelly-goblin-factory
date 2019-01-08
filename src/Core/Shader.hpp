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
    uint32 unifModel;
    uint32 unifView;
    uint32 unifUVPos;
    uint32 unifUVSize;
    uint32 unifColor;

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
    void setMatrixUniforms(Matrix3 model, Matrix3 view);
    void setVertexUniforms(Vector2 pos, Vector2 size);
    void setUVUniforms(Vector2 pos, Vector2 size);
    void setColorUniforms(Color col);
};


#endif // __SHADER_H__
