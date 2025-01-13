/*
 * @Author: Vanish
 * @Date: 2024-09-12 14:40:12
 * @LastEditTime: 2025-01-13 21:00:03
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

#include <string>

#include <glad/glad.h>

class Shader
{
public:
    Shader(){};
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath,const std::string name);
    Shader(const std::string &vertexShaderPath, const std::string &geometryShaderPath, const std::string &fragmentShadrPath, const std::string name );
    ~Shader(){};

public:
    std::string name;
    unsigned int shaderProgramID;

public:
    void Use();

public:
    void InitShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath,const std::string name);
    void InitShader(const std::string &vertexShaderPath, const std::string &geometryShaderPath, const std::string &fragmentShadrPath, const std::string name);
private:
    void CheckCompileErrors(GLuint shader, std::string type);
};