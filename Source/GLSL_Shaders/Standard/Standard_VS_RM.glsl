#version 330 core

layout(location = 0) in vec3 aPos;          // 顶点位置
layout(location = 1) in vec3 aNormal;       // 法线
layout(location = 2) in vec2 aTexCoord;     // 顶点纹理坐标

uniform mat4 model;                         // 模型矩阵
uniform mat4 view;                          // 视图矩阵
uniform mat4 projection;                    // 投影矩阵

uniform sampler2D normalMap;                // 法线贴图

out vec2 uv;                                // 传递到片段着色器的纹理坐标
out vec3 normal;                            // 传递到片段着色器的法线
out vec4 gl_Position;                       // 传递到片段着色器的顶点位置

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    uv = aTexCoord;

    // 从法线贴图中获取法线
    normal = texture(normalMap, aTexCoord).rgb * 2.0 - 1.0; // 将法线从[0, 1]范围映射到[-1, 1]
}
