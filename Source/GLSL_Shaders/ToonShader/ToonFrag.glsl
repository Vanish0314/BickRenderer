#version 330 core

struct DirLight {
    vec3 dir;
    vec3 color;
    vec3 radiant;
};

struct PointLight {
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
in vec3 worldNormal; // 法线
in vec2 uv;          // 纹理坐标

uniform DirLight dirLight;   // 方向光
uniform PointLight pointLight[NR_POINT_LIGHTS]; // 点光源

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

void main() {
    float edgeThickness = 0.1;  // 描边厚度
    float edgeThreshold = 0.1;   // 描边阈值
    // 计算基础颜色
    vec4 baseColor = texture(albedo, uv);
    vec3 norm = normalize(modelNormal);
    vec3 viewDir = normalize(viewPos - worldPos);

    // 光照计算
    vec3 lighting = computeDirLight(dirLight, norm, viewDir);

    //分级
    float step = dot(normalize(worldNormal), -dirLight.dir);
    if (step > 0.8) {
        step = 1;
    } else if (step > 0.5) {
        step = 0.5;
    } else {
        step = 0.2;
    }
    lighting *= step;

    // 描边效果
    vec3 offset = normalize(cross(dFdx(worldPos), dFdy(worldPos))) * edgeThickness;
    vec3 fragPosOffset = worldPos + offset;

    vec4 sampleColor = texture(albedo, uv + offset.xy);
    if (length(sampleColor.rgb - baseColor.rgb) > edgeThreshold) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0); // 描边颜色
    } else {
        FragColor = vec4(baseColor.rgb * lighting, 1.0); // 应用光照和卡通颜色
    }
    FragColor = vec4(baseColor.rgb * lighting, 1.0); // 应用光照和卡通颜色
}
