#version 330 core

struct GeometryToFragment {
    vec3 modelNormal;   // 模型空间法线
    vec3 worldPos;      // 世界坐标
    vec3 worldNormal;   // 世界空间法线
    vec2 uv;            // UV坐标
    vec3 vertexColor;   // 顶点颜色
};

// 使用来自几何着色器的输出结构体
in GeometryToFragment fragData; // 从几何着色器接收的数据

uniform sampler2D albedo;   // 颜色纹理
uniform sampler2D metallic;  // 金属度纹理
uniform sampler2D roughness; // 粗糙度纹理
uniform sampler2D emission;  // 发光纹理
uniform sampler2D ao;        // 环境光遮蔽纹理

uniform vec3 lightPos;       // 光源位置
uniform vec3 viewPos;        // 观察者位置

out vec4 FragColor;          // 输出颜色

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0); // 光照颜色
    vec3 objectColor = texture(albedo, fragData.uv).rgb; // 物体颜色

    vec3 norm = normalize(fragData.worldNormal);    // 使用传递来的世界法线
    vec3 lightDir = normalize(lightPos - fragData.worldPos); // 指向光源的方向
    vec3 viewDir = normalize(viewPos - fragData.worldPos);   // 指向观察者的方向

    // 计算漫反射分量
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 计算高光分量
    vec3 halfDir = normalize(lightDir + viewDir); // 计算半程向量
    float spec = pow(max(dot(norm, halfDir), 0.0), 32.0); // 32 为高光的锐度
    vec3 specular = lightColor * spec;

    // 计算最终颜色
    vec3 result = (diffuse + specular) * objectColor; 
    
    // 使用 fragData 访问 vertexColor
    FragColor = vec4(fragData.vertexColor, 1.0); // 将高光、漫反射和顶点颜色结合
}
