/*
 * @Author: Vanish
 * @Date: 2024-09-14 17:08:09
 * @LastEditTime: 2024-10-15 18:17:34
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

#include <string>
#include <vector>
#include <memory>

#include "glm/glm.hpp"
#include "glad/glad.h"

#include "Object/Object.hpp"
#include "Shader/Shader.hpp"
#include "Material/MatFactory.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

class Mesh{
public:
    std::shared_ptr<std::vector<Vertex>>        vertices;
    std::shared_ptr<std::vector<unsigned int>>  indices;
    std::shared_ptr<Material>                   material;

private:
    unsigned int VAO, VBO, EBO;

public:
    Mesh(std::shared_ptr<std::vector<Vertex>> vertices, std::shared_ptr<std::vector<unsigned int>> indices, std::shared_ptr<Material> material);
    ~Mesh(){};

    void InitializeMesh();
    void DrawMesh(Transform myTransform);
};