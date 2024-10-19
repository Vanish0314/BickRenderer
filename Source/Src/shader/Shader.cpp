/*
 * @Author: Vanish
 * @Date: 2024-09-12 14:40:07
 * @LastEditTime: 2024-09-20 16:51:57
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#include "Shader/Shader.hpp"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,std::string name)
{
    this->name = name;

    std::ifstream vertexShaderStream, fragmentShaderStream;
    std::stringstream vertexShaderCode, fragmentShaderCode;

    vertexShaderStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vertexShaderStream.open(vertexShaderPath,std::ios::in);
        fragmentShaderStream.open(fragmentShaderPath,std::ios::in);

        if(!vertexShaderStream.is_open() ||!fragmentShaderStream.is_open())
        {
            throw std::runtime_error("[Shader.cpp]打开着色器文件失败.");
        }

        vertexShaderCode << vertexShaderStream.rdbuf();
        vertexShaderStream.close();
        
        fragmentShaderCode << fragmentShaderStream.rdbuf();
        fragmentShaderStream.close();

        std::string vCode,fCode;
        vCode = vertexShaderCode.str();
        fCode = fragmentShaderCode.str();

        const char *vertexSource = vCode.c_str();
        const char *fragmentSource = fCode.c_str();

        unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
        glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
        glCompileShader(vertexShaderID);
        glCompileShader(fragmentShaderID);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
            std::cerr << "[Shader.cpp]顶点着色器编译失败!\n" << infoLog << std::endl;
        }
        glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
            std::cerr << "[Shader.cpp]片元着色器编译失败!\n" << infoLog << std::endl;
        }
        // link shaders
        shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertexShaderID);
        glAttachShader(shaderProgramID, fragmentShaderID);
        glLinkProgram(shaderProgramID);
        // check for linking errors
        glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
            std::cerr << "[Shader.cpp]着色器链接失败!\n" << infoLog << std::endl;
        }
        // delete shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
    
}

Shader::Shader(const std::string &vertexShaderPath, const std::string &geometryShaderPath, const std::string &fragmentShaderPath,std::string name)
{
    this->name = name;

    std::ifstream vertexShaderStream,geometryShaderStream ,fragmentShaderStream;
    std::stringstream vertexShaderCode,geometryShaderCode , fragmentShaderCode;

    vertexShaderStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    geometryShaderStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vertexShaderStream.open(vertexShaderPath,std::ios::in);
        geometryShaderStream.open(geometryShaderPath,std::ios::in);
        fragmentShaderStream.open(fragmentShaderPath,std::ios::in);

        if(!vertexShaderStream.is_open() ||!fragmentShaderStream.is_open()||!geometryShaderStream.is_open())
        {
            throw std::runtime_error("Failed to open shader files.");
        }

        vertexShaderCode << vertexShaderStream.rdbuf();
        vertexShaderStream.close();

        geometryShaderCode << geometryShaderStream.rdbuf();
        geometryShaderStream.close();
        
        fragmentShaderCode << fragmentShaderStream.rdbuf();
        fragmentShaderStream.close();

        std::string vCode,gCode,fCode;
        vCode = vertexShaderCode.str();
        gCode = geometryShaderCode.str();
        fCode = fragmentShaderCode.str();

        const char *vertexSource = vCode.c_str();
        const char *geometrySource = gCode.c_str();
        const char *fragmentSource = fCode.c_str();

        unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        unsigned int geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
        unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
        glShaderSource(geometryShaderID, 1, &geometrySource, NULL);
        glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
        glCompileShader(vertexShaderID);
        glCompileShader(geometryShaderID);
        glCompileShader(fragmentShaderID);
        // check for shader compile errors
        CheckCompileErrors(vertexShaderID, "VERTEX");
        CheckCompileErrors(geometryShaderID, "GEOMETRY");
        CheckCompileErrors(fragmentShaderID, "FRAGMENT");

        // link shaders
        shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertexShaderID);
        glAttachShader(shaderProgramID, geometryShaderID);
        glAttachShader(shaderProgramID, fragmentShaderID);
        glLinkProgram(shaderProgramID);
        CheckCompileErrors(shaderProgramID, "PROGRAM");

        // delete shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShaderID);
        glDeleteShader(geometryShaderID);
        glDeleteShader(fragmentShaderID);
    }
    catch (const std::exception& e)
    {
        std::cerr<<"[Shader.cpp]着色器程序初始化失败!\n";
        std::cerr<<"错误:" << e.what() << std::endl<<std::endl;
        return;
    }
}

void Shader::Use()
{
    glUseProgram(shaderProgramID);
}

void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
    int success;
    char infoLog[512];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "Shader compilation error of type: " << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "Program linking error of type: " << type << "\n" << infoLog << std::endl;
        }
    }
}