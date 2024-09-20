#pragma once

#include <memory>
#include "Shader/Shader.hpp"

class Material
{
public:
    std::shared_ptr<Shader> shader;

public:
    Material(std::shared_ptr<Shader> shader) : shader(shader) {}

public:
    virtual void Use() = 0;
};