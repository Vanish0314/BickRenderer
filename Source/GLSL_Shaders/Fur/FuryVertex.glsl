#version 330 core

// 定义用于从顶点着色器传递到几何着色器的结构体
struct VertexToGeometry {
    vec3 modelNormal;   // 模型空间法线
    vec3 worldNormal;   // 世界空间法线
    vec3 worldPos;      // 世界坐标
    vec2 uv;            // UV坐标
    vec3 vertexColor;
};

layout(location = 0) in vec3 aPos;          // 顶点位置
layout(location = 1) in vec3 aNormal;       // 法线
layout(location = 2) in vec2 aTexCoord;     // 顶点纹理坐标

uniform mat4 model;                         // 模型矩阵
uniform mat4 view;                          // 视图矩阵
uniform mat4 projection;                    // 投影矩阵
uniform mat3 normalMatrix_ModelToWorld;     // 法线矩阵(模型空间到世界空间的变换矩阵)

out VertexToGeometry vertexData;            // 输出结构体

void main()
{
    vec4 worldPosition = model * vec4(aPos, 1.0);
    gl_Position = projection * view * worldPosition;

    // 打包输出数据到结构体
    vertexData.modelNormal = aNormal;
    vertexData.worldNormal = normalize(normalMatrix_ModelToWorld * aNormal);
    vertexData.worldPos = vec3(worldPosition);
    vertexData.uv = aTexCoord;
}
