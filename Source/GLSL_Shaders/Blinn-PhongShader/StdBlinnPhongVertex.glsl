#version 330 core

layout(location = 0) in vec3 aPos;          // 顶点位置
layout(location = 1) in vec3 aNormal;       // 法线
layout(location = 2) in vec2 aTexCoord;     // 顶点纹理坐标

uniform mat4 model;                         // 模型矩阵
uniform mat4 view;                          // 视图矩阵
uniform mat4 projection;                    // 投影矩阵
uniform mat3 normalMatrix_ModelToWorld;     // 法线矩阵(模型空间到世界空间的变换矩阵)

uniform sampler2D normalMap;                // 法线贴图

out vec3 modelNormal;
out vec3 worldPos;
out vec3 worldNormal;
out vec2 uv;

void main()
{
    worldPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    modelNormal = aNormal;
    worldNormal = normalize(normalMatrix_ModelToWorld * aNormal);
    uv = aTexCoord;
}