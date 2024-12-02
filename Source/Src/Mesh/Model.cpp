/*
 * @Author: Vanish
 * @Date: 2024-09-19 21:30:14
 * @LastEditTime: 2024-10-11 14:48:09
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#include "Mesh/Model.hpp"
#include "Material/MatFactory.hpp"

Model::Model(std::string const path,MatFactory *matFactory,Transform transform)
:Object(transform)
{
    std::cout <<"[Model.cpp]开始加载模型..."<<"路径:"<<path << std::endl;
    LoadModel(path, matFactory);
    std::cout <<"[Model.cpp]模型加载完成！"<<"路径:"<<path << std::endl;
}

Model::~Model(){}

void Model::Draw()
{
    for(auto &mesh : meshes)
        mesh.DrawMesh(transform);
}

void Model::LoadModel(std::string const path,MatFactory *matFactory)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||!scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::"<<"草了,模型加载失败!\n错误:" << importer.GetErrorString() << std::endl<<std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene, matFactory);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene, MatFactory *matFactory)
{
    // 处理网格
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(ProcessMesh(mesh, scene, matFactory));         
    }
    // 处理子节点
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, matFactory);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, MatFactory *matFactory)
{
    std::shared_ptr<std::vector<Vertex>> vertices      = std::make_shared<std::vector<Vertex>>();
    std::shared_ptr<std::vector<unsigned int>> indices = std::make_shared<std::vector<unsigned int>>();

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; 
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z; 
        vertex.position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = vec;
        }
        else
        {
            vertex.uv = glm::vec2(0.0f, 0.0f);
        }

        vertices->push_back(vertex);
    }
    // 处理索引
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices->push_back(face.mIndices[j]);
    }
    // 处理材质
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        auto mat = std::shared_ptr<Material>(matFactory->CreateMaterial(material, directory));
        return Mesh(vertices, indices, mat);
    }
    else
    {
        std::cout << "ERROR::ASSIMP::"<<"麻了,没有材质!" << std::endl;
        return Mesh(
            vertices,
            indices,
            std::shared_ptr<Material>(matFactory->CreateMaterial(nullptr, directory))
            );
    }


}