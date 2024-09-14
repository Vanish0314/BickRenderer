#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 texCoord;

uniform mat4 transform;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
   // transform = projectionMatrix * viewMatrix * modelMatrix * transform;
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_Position;
   gl_Position = transform * gl_Position;
   texCoord = aTexCoord;
}