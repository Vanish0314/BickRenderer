/*
 * @Author: Vanish
 * @Date: 2024-09-19 21:30:00
 * @LastEditTime: 2024-10-15 18:27:22
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

class MatFactory;
class Model;
class Mesh;

#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh/Mesh.hpp"
#include "Object/Object.hpp"
#include "Material/MatFactory.hpp"

class Model : public Object
{
public:
    std::vector<Mesh> meshes;
    std::string directory;

public:
    Model(std::string const path,MatFactory *matFactory,Transform transform);
    ~Model();

public:
    void Draw();

private:
    void LoadModel(std::string const path,MatFactory *matFactory);
    void ProcessNode(aiNode *node, const aiScene *scene,MatFactory *matFactory);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene,MatFactory *matFactory);
};