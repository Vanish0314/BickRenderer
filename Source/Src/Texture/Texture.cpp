/*
 * @Author: Vanish
 * @Date: 2024-09-12 20:57:24
 * @LastEditTime: 2024-09-23 20:07:12
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#include "Texture/Texture.hpp"

Texture::Texture(std::string filePath,GLenum textureSlotIndex)
{
    this->textureSlotIndex = textureSlotIndex;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "加载材质失败" << std::endl;
        return;
    }
    glGenTextures(1, &id);
    glActiveTexture(textureSlotIndex);
    glBindTexture(GL_TEXTURE_2D, id);
    switch (nrChannels)
    {
        case 1:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
            break;
        case 2:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
            break;
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        default:
            std::cout << "不支持的纹理格式" << std::endl;
            break;
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
} 

void Texture::Activate(unsigned int shaderProgramID,std::string uniformName)
{
    if(id == 0)
        return;

    glActiveTexture(textureSlotIndex);
    glBindTexture(GL_TEXTURE_2D, id);
    glUniform1i(glGetUniformLocation(shaderProgramID, uniformName.c_str()), textureSlotIndex-GL_TEXTURE0);
}