/*
 * @Author: Vanish
 * @Date: 2024-09-20 10:52:37
 * @LastEditTime: 2024-09-20 17:33:11
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

#include "Material/Material.hpp"
#include "Texture/Texture.hpp"

class Mat_StandardPBM_MetallicWorkFlow : public Material
{
public:
    static const std::string defaultAlbedoPath;
    static const std::string defaultMetallicPath;
    static const std::string defaultRoughnessPath;
    static const std::string defaultNormalPath;
    static const std::string defaultHeightPath;
    static const std::string defaultEmissionPath;
    static const std::string defaultAOPath;

public:
    std::shared_ptr<Texture> albedo   ;
    std::shared_ptr<Texture> metallic ;
    std::shared_ptr<Texture> roughness;
    std::shared_ptr<Texture> normalMap;
    std::shared_ptr<Texture> heightMap;
    std::shared_ptr<Texture> emission ;
    std::shared_ptr<Texture> ao       ;

public:
    Mat_StandardPBM_MetallicWorkFlow(std::shared_ptr<Shader> shader) : Material(shader)
    {
        albedo = std::make_shared<Texture>(Texture(defaultAlbedoPath, GL_TEXTURE0));
        metallic = std::make_shared<Texture>(Texture(defaultMetallicPath, GL_TEXTURE1));
        roughness = std::make_shared<Texture>(Texture(defaultRoughnessPath, GL_TEXTURE2));
        normalMap = std::make_shared<Texture>(Texture(defaultNormalPath, GL_TEXTURE3));
        heightMap = std::make_shared<Texture>(Texture(defaultHeightPath, GL_TEXTURE4));
        emission = std::make_shared<Texture>(Texture(defaultEmissionPath, GL_TEXTURE5));
        ao = std::make_shared<Texture>(Texture(defaultAOPath, GL_TEXTURE6));
    }
    
    Mat_StandardPBM_MetallicWorkFlow(std::shared_ptr<Texture> albedo,
                                     std::shared_ptr<Texture> metallic,
                                     std::shared_ptr<Texture> roughness,
                                     std::shared_ptr<Texture> normalMap,
                                     std::shared_ptr<Texture> heightMap,
                                     std::shared_ptr<Texture> emission,
                                     std::shared_ptr<Texture> ao,
                                     std::shared_ptr<Shader> shader)

        : Material(shader),
          albedo(albedo),
          metallic(metallic),
          roughness(roughness),
          normalMap(normalMap),
          heightMap(heightMap),
          emission(emission),
          ao(ao)
    {
    }

    ~Mat_StandardPBM_MetallicWorkFlow() {}

public:
    void Use() override;

};