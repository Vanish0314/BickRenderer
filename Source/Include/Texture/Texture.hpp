/*
 * @Author: Vanish
 * @Date: 2024-09-12 20:57:16
 * @LastEditTime: 2024-09-20 13:26:15
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

#include <string>
#include <iostream>
#include "glad/glad.h"

#include "stb_image.h"


class Texture
{
public:
    unsigned int id;
    int width, height, nrChannels;
    GLenum textureSlotIndex;
    

public:
    Texture(std::string filePath,GLenum textureSlotIndex);
    ~Texture(){};

public:
    void Activate(unsigned int shaderProgramID,std::string uniformName);
};