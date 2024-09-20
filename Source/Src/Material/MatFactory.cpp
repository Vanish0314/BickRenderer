#include "Material/MatFactory.hpp"

Material* MatFactory_StandardPBM_MetallicWorkFlow::CreateMaterial(aiMaterial *mat, std::string resRootPath) 
{
    aiString path;
    std::string pathHead = resRootPath + "/";
    std::string strPath;

    // albedo
    path.Clear();
    strPath.clear();
    mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
    std::shared_ptr<Texture> albedo;
    if (path.length != 0)
    {
        strPath = pathHead + path.C_Str();
    }
    else
    {
        strPath = Mat_StandardPBM_MetallicWorkFlow::defaultAlbedoPath;
    }
    albedo = std::make_shared<Texture>(strPath, GL_TEXTURE0);

    // metallic
    path.Clear();
    strPath.clear();
    mat->GetTexture(aiTextureType_METALNESS, 0, &path); 
    std::shared_ptr<Texture> metallic;
    if (path.length != 0)
    {
        strPath = pathHead + path.C_Str();
    }
    else
    {
        strPath = Mat_StandardPBM_MetallicWorkFlow::defaultMetallicPath;
    }
    metallic = std::make_shared<Texture>(strPath, GL_TEXTURE1);

    // roughness
    path.Clear();
    strPath.clear();
    mat->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &path);
    std::shared_ptr<Texture> roughness;
    if (path.length != 0)
    {
        strPath = pathHead + path.C_Str();
    }
    else
    {
        strPath = Mat_StandardPBM_MetallicWorkFlow::defaultRoughnessPath;
    }
    roughness = std::make_shared<Texture>(strPath, GL_TEXTURE2);

    // normal
    path.Clear();
    strPath.clear();
    mat->GetTexture(aiTextureType_NORMALS, 0, &path);
    std::shared_ptr<Texture> normal;
    if (path.length != 0)
    {
        strPath = pathHead + path.C_Str();
    }
    else
    {
        strPath = Mat_StandardPBM_MetallicWorkFlow::defaultNormalPath;
    }
    normal = std::make_shared<Texture>(strPath, GL_TEXTURE3);

    // heightmap
    path.Clear();
    strPath.clear();
    mat->GetTexture(aiTextureType_HEIGHT, 0, &path);
    std::shared_ptr<Texture> heightmap;
    if (path.length != 0)
    {
        strPath = pathHead + path.C_Str();
    }
    else
    {
        strPath = Mat_StandardPBM_MetallicWorkFlow::defaultHeightPath;
    }
    heightmap = std::make_shared<Texture>(strPath, GL_TEXTURE4);

    // emissive
    path.Clear();
    strPath.clear();
    mat->GetTexture(aiTextureType_EMISSIVE, 0, &path);
    std::shared_ptr<Texture> emissive;
    if (path.length != 0)
    {
        strPath = pathHead + path.C_Str();
    }
    else
    {
        strPath = Mat_StandardPBM_MetallicWorkFlow::defaultEmissionPath;
    }
    emissive = std::make_shared<Texture>(strPath, GL_TEXTURE6);

    // ambient occlusion
    path.Clear();
    strPath.clear();
    mat->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &path);
    std::shared_ptr<Texture> ambientOcclusion;
    if (path.length != 0)
    {
        strPath = pathHead + path.C_Str();
    }
    else
    {
        strPath = Mat_StandardPBM_MetallicWorkFlow::defaultAOPath;
    }
    ambientOcclusion = std::make_shared<Texture>(strPath, GL_TEXTURE5);

    Mat_StandardPBM_MetallicWorkFlow *material = new Mat_StandardPBM_MetallicWorkFlow(
        albedo,
        metallic,
        roughness,
        normal,
        heightmap,
        emissive,
        ambientOcclusion,
        shader
    );

    return material;
}
