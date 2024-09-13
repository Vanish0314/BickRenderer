/*
 * @Author: Vanish
 * @Date: 2024-09-12 14:40:12
 * @LastEditTime: 2024-09-12 19:23:06
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

class Shader
{
public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath,const std::string name = "default");
    Shader(const std::string &vertexShaderPath, const std::string &geometryShaderPath, const std::string &fragmentShaderPath, const std::string name = "default");
    ~Shader(){};

public:
    std::string name;
    unsigned int shaderProgramID;

public:
    void Use();

private:
    void CheckCompileErrors(GLuint shader, std::string type);
};