#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct vec2;
struct Color;
struct mat4;

class  Shader
{
private:
    unsigned int pShaderProgram;
    std::string pVertexShaderPath, pFragmentShaderPath;
    std::string pVertexShaderCode, pFragmentShaderCode;

private:
    std::string ParseShader(const std::string& filePath);
    unsigned int CompileShader(unsigned int shaderType, const std::string& shaderCode);
    
public:
    Shader(const std::string& vsPath, const std::string& fsPath);
    ~Shader();

    void Bind();
    void Unbind();

    void SetUniform1f(const char* name, float value);
    void SetUniform1i(const char* name, int value);
    void SetUniformVec2f(const char* name, const vec2& vec);
    void SetUniformColor4f(const char* name, const Color& color);
    void SetUniformMat4f(const char* name, const mat4& matrix);
};

