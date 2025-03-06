#pragma once

#include <iostream>

#define  TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"
#include "Mesh/Model.hpp"

class glTFImporter
{
public:
    bool Load(Model &model,std::string filepath);
};