#pragma once

#include "Light/Light.hpp"

class DirectionalLight : public Light
{
public:
    glm::vec3 direction;

public:
    DirectionalLight()
    : Light()
    {
        direction = glm::vec3(0.0f, -1.0f, 0.0f);
    }

    DirectionalLight(glm::vec3 direction)
    : Light()
    {
        this->direction = glm::normalize(direction);
    }

    DirectionalLight(glm::vec3 direction,glm::vec3 position, glm::vec3 color, float radiant)
    :Light(position, color, radiant)
    {
        this->direction = glm::normalize(direction);
    }

    ~DirectionalLight(){}
};