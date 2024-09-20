#pragma once

#include <memory>
#include "Material/Material.hpp"
#include "Material/Mat_StandardPBM_MetallicWorkFlow.hpp"
#include "assimp/material.h"

class MatFactory
{
public:
    std::shared_ptr<Shader> shader;
public:
    MatFactory() {}
    virtual ~MatFactory() {}

public:
    virtual Material *CreateMaterial(aiMaterial* mat, std::string resRootPath) = 0;
};

class MatFactory_StandardPBM_MetallicWorkFlow : public MatFactory
{
public:
    std::string stdVertexShaderPath = "Source/GLSL_Shaders/Standard/Standard_VS_RM.glsl";
    std::string stdGeometryShaderPath = "Source/GLSL_Shaders/Standard/Standard_GS_RM.glsl";
    std::string stdFragmentShaderPath = "Source/GLSL_Shaders/Standard/Standard_FS_RM.glsl";

    MatFactory_StandardPBM_MetallicWorkFlow(std::string vsPath, std::string gsPath, std::string fsPath)
    : stdVertexShaderPath(vsPath), stdGeometryShaderPath(gsPath), stdFragmentShaderPath(fsPath)
    {
        std::string name = vsPath.substr(vsPath.find_last_of("/") + 1);
        shader = std::make_shared<Shader>(stdVertexShaderPath, stdGeometryShaderPath, stdFragmentShaderPath, name);
    }

    MatFactory_StandardPBM_MetallicWorkFlow(std::string vsPath, std::string fsPath)
    : stdVertexShaderPath(vsPath), stdFragmentShaderPath(fsPath)
    {
        std::string name = vsPath.substr(vsPath.find_last_of("/") + 1);
        shader = std::make_shared<Shader>(stdVertexShaderPath, "", stdFragmentShaderPath, name);
    }

    MatFactory_StandardPBM_MetallicWorkFlow()
    {
        std::string name = stdVertexShaderPath.substr(stdVertexShaderPath.find_last_of("/") + 1);
        shader = std::make_shared<Shader>(stdVertexShaderPath, stdGeometryShaderPath, stdFragmentShaderPath, name);
    }

    ~MatFactory_StandardPBM_MetallicWorkFlow() {}

public:
    Material *CreateMaterial(aiMaterial* mat, std::string resRootPath) override;
};