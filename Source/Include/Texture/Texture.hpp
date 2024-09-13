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
    std::string texName;

public:
    Texture(std::string filename,GLenum textureSlotIndex,std::string texName = "default");
    ~Texture(){};

public:
    void Activate(unsigned int shaderProgramID,std::string uniformName);
};