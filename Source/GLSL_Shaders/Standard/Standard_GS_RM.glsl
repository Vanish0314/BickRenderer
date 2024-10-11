#version 330 core

layout(triangles) in;  
layout(triangle_strip, max_vertices = 3) out;

uniform sampler2D heightMap;

out vec2 fragTexCoords; // 用于传递纹理坐标到片段着色器

void main()
{
    for (int i = 0; i < 3; i++)
    {
        vec2 texCoords = gl_in[i].gl_Position.xy; // 根据实际情况计算纹理坐标
        float height = texture(heightMap, texCoords).r; // 从高度图中获取高度
        gl_Position = vec4(gl_in[i].gl_Position.x, gl_in[i].gl_Position.y, height, 1.0); // 更新Z坐标

        fragTexCoords = texCoords; // 传递纹理坐标
        gl_Position = gl_Position;
        EmitVertex(); // 输出顶点
    }
    
    EndPrimitive(); // 结束三角形的输出
}
