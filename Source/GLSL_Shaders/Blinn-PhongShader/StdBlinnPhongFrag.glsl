#version 330 core
struct DirLight
{
    vec3 dir;
    vec3 color;
    vec3 radiant;
};
struct PointLight
{
    vec3 pos;
    vec3 color;
    vec3 radint;

    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS 4

in vec3 modelNormal;
in vec3 worldPos;    // 世界坐标
in vec3 worldNormal;      // 法线
in vec2 uv;          // 纹理坐标

uniform DirLight dirLight;   // 光源位置
uniform PointLight pointLight[NR_POINT_LIGHTS]; // 点光源位置

uniform sampler2D albedo;   // 颜色纹理
uniform sampler2D metallic;  // 金属度纹理
uniform sampler2D roughness; // 粗糙度纹理
uniform sampler2D emission;  // 发光纹理
uniform sampler2D ao;        // 环境光遮蔽纹理

uniform vec3 viewPos;        // 观察者位置

out vec4 FragColor;          // 输出颜色

vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir) {
    vec3 lightDir = normalize(-light.dir);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;
    
    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfDir), 0.0), 32.0);
    vec3 specular = spec * light.color;
    
    return diffuse + specular;
}

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.pos - fragPos);
    float distance = length(light.pos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color * attenuation;
    
    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfDir), 0.0), 32.0);
    vec3 specular = spec * light.color * attenuation;
    
    return diffuse + specular;
}

void main() {
    vec3 objectColor = texture(albedo, uv).rgb;
    vec3 norm = normalize(modelNormal);
    vec3 viewDir = normalize(viewPos - worldPos);
    
    // 环境光
    vec3 result = 0.1 * objectColor; 

    // 计算方向光源
    result += computeDirLight(dirLight, norm, viewDir);

    // 计算点光源
    // for (int i = 0; i < NR_POINT_LIGHTS; i++) {
    //     result += computePointLight(pointLight[i], norm, worldPos, viewDir);
    // }

    FragColor = vec4(result * objectColor, 1.0);
}
