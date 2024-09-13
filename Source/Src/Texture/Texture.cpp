#include "Texture/Texture.hpp"

Texture::Texture(std::string filename,GLenum textureSlotIndex,std::string texName)
{
    this->texName = texName;
    this->textureSlotIndex = textureSlotIndex;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
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
        std::cout << "Texture format not supported" << std::endl;

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

} 

void Texture::Activate(unsigned int shaderProgramID,std::string uniformName)
{
    glActiveTexture(textureSlotIndex);
    glBindTexture(GL_TEXTURE_2D, id);
    glUniform1i(glGetUniformLocation(shaderProgramID, uniformName.c_str()), textureSlotIndex-GL_TEXTURE0);
}