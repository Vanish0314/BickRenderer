#version 330 core

in vec3 modelNormal;
in vec3 worldPos;    // 世界坐标
in vec3 worldNormal;      // 法线
in vec2 uv;          // 纹理坐标

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
    vec3 objectColor = texture(albedo, uv).rgb; // 物体颜色

    vec3 norm = normalize(modelNormal);
    vec3 lightDir = normalize(lightPos - worldPos); // 指向光源的方向
    vec3 viewDir = normalize(viewPos - worldPos);   // 指向观察者的方向

    // 计算漫反射分量
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 计算高光分量
    vec3 halfDir = normalize(lightDir + viewDir); // 计算半程向量
    float spec = pow(max(dot(norm, halfDir), 0.0), 32.0); // 32 为高光的锐度
    vec3 specular = lightColor * spec;

    // 计算最终颜色
    vec3 result = (diffuse + specular) * objectColor; 
    FragColor = vec4(result, 1.0);
}