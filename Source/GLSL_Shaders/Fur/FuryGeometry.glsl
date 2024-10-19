#version 330 core

// 定义用于从顶点着色器传递到几何着色器的结构体
struct VertexToGeometry {
    vec3 modelNormal;   // 模型空间法线
    vec3 worldNormal;   // 世界空间法线
    vec3 worldPos;      // 世界坐标
    vec2 uv;            // UV坐标
    vec3 vertexColor;
};

// 定义用于从几何着色器传递到片元着色器的结构体
struct GeometryToFragment {
    vec3 modelNormal;   // 模型空间法线
    vec3 worldPos;      // 世界坐标
    vec3 worldNormal;   // 世界空间法线
    vec2 uv;            // UV坐标
    vec3 vertexColor;   // 顶点颜色
};

layout(triangles) in;                       // 输入三角形
layout(line_strip, max_vertices = 2) out;    // 输出线段 (每个毛发段产生两端点)

in VertexToGeometry vertexData[];  // 输入数组，用于接收顶点着色器的数据

uniform float hairLength = 0.2;  
uniform int hairSegments = 5;    

uniform mat4 view;         
uniform mat4 projection;    

out GeometryToFragment fragData; // 输出结构体

void main() {
    // 确保 hairSegments 为正值
    if (hairSegments <= 0) {
        return;
    }

    // 对三角形的每个顶点生成毛发段的线段
    for (int i = 0; i < 3; ++i) {
        vec3 position = vertexData[i].worldPos;           
        vec3 normal = normalize(vertexData[i].worldNormal);

        // 计算毛发段的每个顶点，输出为线段
        for (int j = 0; j <= hairSegments; ++j) {
            float t = float(j) / float(hairSegments);
            vec3 offset = normal * hairLength * t;

            vec3 hairPos = position + offset;   

            // 输出每个毛发段的端点作为线段
            vec4 viewPos = view * vec4(hairPos, 1.0);
            gl_Position = projection * viewPos;

            // 将顶点的世界坐标和颜色传递到片元着色器
            fragData.modelNormal = vertexData[i].modelNormal;
            fragData.worldPos = hairPos;
            fragData.worldNormal = normal;
            fragData.uv = vertexData[i].uv;
            fragData.vertexColor = vertexData[i].vertexColor;

            // 发射第一个端点
            EmitVertex();

            // 为了绘制线段，需要输出两个端点
            // 计算另一个端点，假设我们在每个毛发段的最后一个位置也生成一个线段
            if (j == hairSegments) {
                vec3 finalHairPos = position + normal * hairLength;
                viewPos = view * vec4(finalHairPos, 1.0);
                gl_Position = projection * viewPos;

                fragData.modelNormal = vertexData[i].modelNormal;
                fragData.worldPos = finalHairPos;
                fragData.worldNormal = normal;
                fragData.uv = vertexData[i].uv;
                fragData.vertexColor = vertexData[i].vertexColor;

                // 发射第二个端点
                EmitVertex();
            }
        }
        EndPrimitive();  // 每个三角形的处理结束，结束当前的 primitive
    }
}
