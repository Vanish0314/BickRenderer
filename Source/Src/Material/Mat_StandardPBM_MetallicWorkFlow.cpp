/*
 * @Author: Vanish
 * @Date: 2024-09-20 10:53:17
 * @LastEditTime: 2024-10-19 21:03:18
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


void Mat_StandardPBM_MetallicWorkFlow::Use(Transform myTransform)
{
    //TODO:填充顶点,更新各种参数
    shader->Use();
#pragma region Positions
    unsigned short viewPosLoc = glGetUniformLocation(shader->shaderProgramID, "viewPos");
    glm::vec3 viewPos = Camera::main->position;
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(viewPos));

#pragma endregion

#pragma region Light

    // Directional Light 只使用第一个
    unsigned short directionalLightDirLoc = glGetUniformLocation(shader->shaderProgramID, "dirLight.dir");
    unsigned short directionalLightColorLoc = glGetUniformLocation(shader->shaderProgramID, "dirLight.color");
    unsigned short directionalLightRadiantLoc = glGetUniformLocation(shader->shaderProgramID, "dirLight.radiant");
    glm::vec3 directionalLightDir = Singleton<Scene>::Instance().directionalLights.at(0)->direction;
    glm::vec3 directionalLightColor = Singleton<Scene>::Instance().directionalLights.at(0)->color;
    float directionalLightRadiant = Singleton<Scene>::Instance().directionalLights.at(0)->radiant;
    glUniform3fv(directionalLightDirLoc, 1, glm::value_ptr(directionalLightDir));
    glUniform3fv(directionalLightColorLoc, 1, glm::value_ptr(directionalLightColor));
    glUniform1f(directionalLightRadiantLoc, directionalLightRadiant);

    //TODO: Point Light
#pragma endregion

#pragma region MVP...
    glm::mat4 modelMatrix(1.0f);
    glm::mat4 viewMatrix(1.0f);
    glm::mat4 projectionMatrix(1.0f);
    modelMatrix      = glm::translate(modelMatrix, myTransform.position);
    modelMatrix      = glm::rotate(modelMatrix, glm::radians(myTransform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix      = glm::rotate(modelMatrix, glm::radians(myTransform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix      = glm::rotate(modelMatrix, glm::radians(myTransform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix      = glm::scale(modelMatrix, myTransform.scale);
    viewMatrix       = Camera::main->GetViewMatrix();
    projectionMatrix = Camera::main->GetProjectionMatrix();
    unsigned short modelLoc      = glGetUniformLocation(shader->shaderProgramID, "model");
    unsigned short viewLoc       = glGetUniformLocation(shader->shaderProgramID, "view");
    unsigned short projectionLoc = glGetUniformLocation(shader->shaderProgramID, "projection");
    glUniformMatrix4fv(modelLoc     , 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewLoc      , 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));    

    glm::mat4 normalMatrix_ModelToWorld = glm::transpose(glm::inverse(modelMatrix));
    unsigned short normalMatrixLoc = glGetUniformLocation(shader->shaderProgramID, "normalMatrix");
    glUniformMatrix4fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix_ModelToWorld));
#pragma endregion
    
#pragma region Textures
    albedo   ->Activate(shader->shaderProgramID,"albedo");
    metallic ->Activate(shader->shaderProgramID,"metallic");
    roughness->Activate(shader->shaderProgramID,"roughness");
    normalMap->Activate(shader->shaderProgramID,"normalMap");
    heightMap->Activate(shader->shaderProgramID,"heightMap");
    emission ->Activate(shader->shaderProgramID,"emission");
    ao       ->Activate(shader->shaderProgramID,"ao");
#pragma endregion
}