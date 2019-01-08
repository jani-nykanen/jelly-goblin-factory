// Shader
// (c) 2019 Jani Nykänen

#include "Shader.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <stdexcept>

// Constants
#define ERR_BUFFER_SIZE 4096


// Default shaders
static const std::string DEF_VERTEX = 
"#version 120\n"
"attribute vec2 vertexPos;\n"
"attribute vec2 vertexUV;\n"
"uniform mat3 model;\n"
"uniform mat3 view;\n"
"uniform vec2 pos;\n"
"uniform vec2 size;\n"
"varying vec2 uv;\n"
"void main() {\n"
"    vec2 p = vertexPos.xy;\n"
"    p.x *= size.x;\n"
"	 p.y *= size.y;\n"
"	 p += pos;\n"
"    gl_Position = vec4(view * model * vec3(p.x, p.y, 1), 1);\n"
"    uv = vertexUV; \n"
"}\n";
static const std::string DEF_FRAG = 
"#version 120\n"
"varying vec2 uv;\n"  
"uniform sampler2D texSampler;\n"  
"uniform vec2 texPos;\n"  
"uniform vec2 texSize;\n"  
"uniform vec4 color;\n"  
"void main() {\n"  
"    const float DELTA = 0.01;\n"  
"    vec2 tex = uv;\n"  
"    tex.x *= texSize.x;\n"  
"    tex.y *= texSize.y;\n"  
"    tex += texPos;\n"  
"    vec4 res = color * texture2D(texSampler, tex);\n"  
"    if(res.a <= DELTA) {\n"  
"        discard;\n"  
"    }\n"  
"    gl_FragColor = res;\n"  
"}";


// Compile a shader
static void compileShader(uint32 &shader, std::string src) {

    char errBuf[ERR_BUFFER_SIZE];

    int infoLen = 0;
    int res = 0;

    // Compile
    const char* s = src.c_str();
    glShaderSource(shader, 1, &s , NULL);
	glCompileShader(shader);

    // Check errors
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
	if(infoLen > 0 ) {

	    glGetShaderInfoLog(shader, infoLen, NULL, errBuf);
		throw std::runtime_error(errBuf);
	}
}


// Link the program
static void linkProgram(uint32 &vertex, uint32 &frag, uint32 &prog) {

    char errBuf[ERR_BUFFER_SIZE];

    int infoLen = 0;
    int res = 0;

    // Link
    prog = glCreateProgram();
	glAttachShader(prog, vertex);
	glAttachShader(prog, frag);
	glLinkProgram(prog);

    // Check errors
    glGetShaderiv(prog, GL_COMPILE_STATUS, &res);
	glGetShaderiv(prog, GL_INFO_LOG_LENGTH, &infoLen);
    if(infoLen > 0 ) {

	    glGetProgramInfoLog(prog, infoLen, NULL, errBuf);
		throw std::runtime_error(errBuf);
	}
}


// Build
void Shader::build(std::string vertexSrc, 
        std::string fragmentSrc) {

    // Create shaders
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile shaders
    compileShader(vertex, vertexSrc);
    compileShader(fragment, fragmentSrc);

    // Bind attribute locations
	glBindAttribLocation(program, 0, "vertexPos");
	glBindAttribLocation(program, 1, "vertexUV");

    // Link program
    linkProgram(vertex, fragment, program);

    // Delete unnecessary stuff
    glDetachShader(program, vertex);
	glDetachShader(program, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


// Constructors
Shader::Shader(std::string vertex, 
        std::string fragment) {

    build(vertex, fragment);
}
Shader::Shader() {

    // Build default
    build(DEF_VERTEX, DEF_FRAG);
}


// Destructor
Shader::~Shader() {

    glDeleteProgram(program);
}


// Use shader
void Shader::useShader() {

    // Use program
    glUseProgram(program);

    // Get uniforms
    unifPos = glGetUniformLocation(program, "pos");
	unifSize = glGetUniformLocation(program, "size");
    unifModel = glGetUniformLocation(program, "model");
    unifView = glGetUniformLocation(program, "view");
    unifUVPos = glGetUniformLocation(program, "texPos");
    unifUVSize = glGetUniformLocation(program, "texSize");
    unifColor = glGetUniformLocation(program, "color");

    // Set defaults
    setMatrixUniforms(Matrix3().identity(), Matrix3().identity());
    setVertexUniforms(Vector2(0, 0), Vector2(1, 1));
    setUVUniforms(Vector2(0, 0), Vector2(1, 1));
    setColorUniforms(Color(1, 1, 1, 1));
}


// Set uniforms
void Shader::setMatrixUniforms(Matrix3 model, Matrix3 view) {

    glUniformMatrix3fv(unifModel, 1, false, model.toArray());
    glUniformMatrix3fv(unifView, 1, false, view.toArray());
}
void Shader::setVertexUniforms(Vector2 pos, Vector2 size) {
    
    glUniform2f(unifPos, pos.x, pos.y);
    glUniform2f(unifSize, size.x, size.y);
}
void Shader::setUVUniforms(Vector2 pos, Vector2 size) {
    
    glUniform2f(unifUVPos, pos.x, pos.y);
    glUniform2f(unifUVSize, size.x, size.y);
}
void Shader::setColorUniforms(Color col) {
    
    glUniform4f(unifColor, col.r, col.g, col.b, col.a);
}
