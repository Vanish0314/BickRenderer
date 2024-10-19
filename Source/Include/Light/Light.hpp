/*
 * @Author: Vanish
 * @Date: 2024-10-15 15:11:05
 * @LastEditTime: 2024-10-19 21:16:53
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
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
        radiant = 10.0f;
    }
    Light(glm::vec3 pos, glm::vec3 col, float rad) {
        position = pos;
        color = col;
        radiant = rad;
    }
    ~Light() {}
};