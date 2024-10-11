/*
 * @Author: Vanish
 * @Date: 2024-09-23 18:39:26
 * @LastEditTime: 2024-09-23 18:59:21
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

#include "glm/glm.hpp"

class Transform
{
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

public:
    Transform() 
    : position(glm::vec3(0.0f)), rotation(glm::vec3(0.0f)), scale(glm::vec3(1.0f)) 
    {}
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
    : position(position), rotation(rotation), scale(scale) 
    {}
    ~Transform() {}
};

class Object
{
public:
    Transform transform;

public:
    Object(Transform transform) : transform(transform) {}
    virtual ~Object() {}
};