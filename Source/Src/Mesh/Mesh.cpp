// #include "Mesh/Mesh.hpp"


// void Mesh::InitializeMesh()
// {
//     glGenVertexArrays(1,&VAO);
//     glBindVertexArray(VAO);

//     glGenBuffers(1, &VBO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    
//     glGenBuffer(1, &EBO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

//     glEnableVertexArrayAttrib(0);
//     glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex), (void*)0);
//     glEnableVertexArrayAttrib(1);
//     glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex), (void*)offsetof(Vertex, Normal));
//     glEnableVertexArrayAttrib(2);
//     glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

//     glBindVertexArray(0);
// }

// void Mesh::DrawMesh()
// {

// }