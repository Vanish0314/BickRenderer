/*
 * @Author: Vanish
 * @Date: 2024-09-20 10:53:17
 * @LastEditTime: 2024-09-20 14:11:22
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#include "Material/Mat_StandardPBM_MetallicWorkFlow.hpp"

const std::string Mat_StandardPBM_MetallicWorkFlow::defaultAlbedoPath = "Assets/DefaultTextures/DefaultAlbedo.png";
const std::string Mat_StandardPBM_MetallicWorkFlow::defaultMetallicPath = "Assets/DefaultTextures/DefaultMetallic.png";
const std::string Mat_StandardPBM_MetallicWorkFlow::defaultRoughnessPath = "Assets/DefaultTextures/DefaultRoughness.png";
const std::string Mat_StandardPBM_MetallicWorkFlow::defaultNormalPath = "Assets/DefaultTextures/DefaultNormal.png";
const std::string Mat_StandardPBM_MetallicWorkFlow::defaultHeightPath = "Assets/DefaultTextures/DefaultHeight.png";
const std::string Mat_StandardPBM_MetallicWorkFlow::defaultEmissionPath = "Assets/DefaultTextures/DefaultEmission.png";
const std::string Mat_StandardPBM_MetallicWorkFlow::defaultAOPath = "Assets/DefaultTextures/DefaultAO.png";


void Mat_StandardPBM_MetallicWorkFlow::Use()
{
    // shader->Use();

    albedo   ->Activate(shader->shaderProgramID,"albedo");
    metallic ->Activate(shader->shaderProgramID,"metallic");
    roughness->Activate(shader->shaderProgramID,"roughness");
    normalMap->Activate(shader->shaderProgramID,"normal");
    heightMap->Activate(shader->shaderProgramID,"height");
    emission ->Activate(shader->shaderProgramID,"emission");
    ao       ->Activate(shader->shaderProgramID,"ao");
}