// #pragma once

// #include <string>
// #include <vector>
// #include "glm/glm.hpp"

// #include "Shader/Shader.hpp"

// struct Vertex
// {
//     glm::vec3 position;
//     glm::vec3 normal;
//     glm::vec2 uv;
// };

// struct Texture
// {
//     std::string name;
//     std::string path;
//     unsigned int glID;
// };

// class Mesh{
// public:
//     std::vector<Vertex> *vertices;
//     std::vector<unsigned int> *indices;
//     std::vector<Texture> *textures;

// private:
//     unsigned int VAO, VBO, EBO;

// public:
//     Mesh(std::string const &path);
//     ~Mesh(){};

//     void InitializeMesh();
//     void DrawMesh(Shader &shader);
// };