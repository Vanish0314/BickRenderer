#pragma once

#include "glm/glm.hpp"

class Light
{
public:
    glm::vec3 position;
    glm::vec3 color;
    float radiant;

public:
    Light(){
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        radiant = 1.0f;
    }
    Light(glm::vec3 pos, glm::vec3 col, float rad) {
        position = pos;
        color = col;
        radiant = rad;
    }
    ~Light() {}
};