#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 texCoord;

// uniform float heightScale;
uniform sampler2D heightMap;
uniform mat4 MVP;

void main()
{
    // vec3 pos = aPos + max(0.01, texture(heightMap, aTexCoords).w) * vec3(0, 0, 1);

    gl_Position = MVP * vec4(aPos, 1.0);
    texCoord = aTexCoords;
}