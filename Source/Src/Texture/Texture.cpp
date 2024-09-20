/*
 * @Author: Vanish
 * @Date: 2024-09-12 20:57:24
 * @LastEditTime: 2024-09-20 16:46:02
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
    if(nrChannels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else if(nrChannels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
    {
        std::cout << "材质格式暂不支持" << std::endl;
        return;
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