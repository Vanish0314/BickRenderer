/*
 * @Author: Vanish
 * @Date: 2024-09-14 17:08:04
 * @LastEditTime: 2024-09-23 19:59:59
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#include "Mesh/Mesh.hpp"

Mesh::Mesh(std::shared_ptr<std::vector<Vertex>> vertices, std::shared_ptr<std::vector<unsigned int>> indices, std::shared_ptr<Material> material)
{
    this->vertices = vertices;
    this->indices = indices;
    this->material = material;

    InitializeMesh();
}

void Mesh::InitializeMesh()
{
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(Vertex), vertices->data(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), indices->data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
}

void Mesh::DrawMesh(Transform myTransform)
{
    glBindVertexArray(VAO);

    material->Use(myTransform);

    glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}