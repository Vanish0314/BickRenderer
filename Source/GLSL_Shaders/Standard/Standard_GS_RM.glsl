#version 330 core

layout(triangles) in;  // 输入为三角形
layout(triangle_strip, max_vertices = 3) out;  // 输出为三角形条带，最大顶点数为3

void main()
{
    // 遍历输入的每个三角形的顶点
    for (int i = 0; i < 3; i++)
    {
        // 直接将输入的顶点位置传递到下一个阶段
        gl_Position = gl_in[i].gl_Position;  
        
        // 输出顶点
        EmitVertex();
    }
    
    // 结束当前的顶点输出
    EndPrimitive();
}