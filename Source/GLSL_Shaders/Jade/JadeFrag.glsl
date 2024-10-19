// 启动深度测试
// 需要关闭背面剔除
// 启用混合
// glEnable(GL_DEPTH_TEST);  // 启用深度测试
// glDepthFunc(GL_LESS);     // 设置深度测试函数为 LESS
// glDepthMask(GL_TRUE);  // 启用深度写入
// glDisable(GL_CULL_FACE);
// glEnable(GL_BLEND);
// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#version 330 core

// 输入
in vec3 modelNormal;   // 模型空间法线
in vec3 worldPos;      // 世界空间位置
in vec3 worldNormal;   // 世界空间法线
in vec2 uv;            // 纹理坐标

// Uniforms
uniform sampler2D albedo;      // 基础颜色纹理（玉石颜色）
uniform sampler2D metallic;    // 金属度纹理
uniform sampler2D roughness;   // 粗糙度纹理
uniform sampler2D emission;    // 发光纹理
uniform sampler2D ao;          // 环境光遮蔽纹理

uniform vec3 lightPos;         // 光源位置
uniform vec3 viewPos;          // 观察者位置
uniform mat4 projectionMatrix; // 投影矩阵，用于计算深度

// 输出颜色
out vec4 FragColor;

const float PI = 3.14159265359;

// 常量（去除uniform变量，直接写入代码中）
const float baseDistortion = 0.2;  // 基础失真
const float basePower = 5.0;       // 基础光照强度
const float baseScale = 1.0;       // 基础缩放

// Blinn-Phong 光照模型
vec3 BlinnPhong(vec3 normal, vec3 lightDir, vec3 viewDir, float shininess) {
    // 计算半程向量
    vec3 H = normalize(lightDir + viewDir);

    // 漫反射项
    float NdotL = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = NdotL * vec3(1.0);  // 使用白色光源

    // 镜面反射项 (Blinn-Phong)
    float NdotH = max(dot(normal, H), 0.0);
    vec3 specular = pow(NdotH, shininess) * vec3(1.0); // 使用白色高光

    return diffuse + specular;
}

// 模拟背光透射光（用于半透明的玉石效果）
vec3 Backlight(vec3 normal, vec3 lightDir, vec3 viewDir) {
    // 加扰动效果（透射光模拟）
    vec3 backDir = normalize(lightDir + normal * baseDistortion);
    float VdotB = max(0, dot(viewDir, backDir));
    float backlightTerm = max(0.0, pow(VdotB, basePower)) * baseScale;

    return backlightTerm * vec3(1.0);  // 使用白色光源
}

// 环境光反射计算（此处去除环境贴图）
vec3 EnvironmentReflection(vec3 normal, vec3 viewDir) {
    // 计算反射方向
    vec3 reflectDir = reflect(-viewDir, normal);

    // 采样环境反射，因去除cubeMap，模拟一个简单的环境反射
    // 这里只是简单使用反射方向模拟
    return vec3(0.3, 0.3, 0.3);  // 返回模拟的环境光颜色
}

// 计算深度（基于Z-buffer）来模拟玉石的透光效果
float ComputeThickness(vec3 fragPos) {
    // 获取当前片元的深度值（视口空间中的深度）
    float currentDepth = gl_FragCoord.z;

    // 将深度值转换为线性深度
    // 通过视口空间到裁剪空间的转换，获取线性深度
    float linearDepth = (2.0 * currentDepth - 1.0) / projectionMatrix[3][2]; 

    // 计算深度差异
    // 注意：这里我们假设已知的模型（fragPos）与深度值的关系
    // 若需要精确透光，深度差异与物体的材质、厚度等因素相关
    float thickness = max(0.0, pow(abs(linearDepth), 2.0)); // 越深透光效果越强
    return thickness;
}

void main() {
    // 从纹理获取材质参数
    vec3 albedoColor = texture(albedo, uv).rgb;  // 基础颜色
    float metallicFactor = texture(metallic, uv).r;  // 金属度
    float roughnessFactor = texture(roughness, uv).r;  // 粗糙度
    vec3 emissionColor = texture(emission, uv).rgb;  // 发光
    float aoFactor = texture(ao, uv).r;  // 环境光遮蔽

    // 计算法线和方向
    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPos - worldPos);
    vec3 viewDir = normalize(viewPos - worldPos);

    // 计算Blinn-Phong光照
    vec3 color = BlinnPhong(normal, lightDir, viewDir, roughnessFactor);

    // 添加背光透射效果（模拟玉石的半透明效果）
    color += Backlight(normal, lightDir, viewDir);

    // 计算环境光反射（简单模拟，没有cubeMap）
    color += EnvironmentReflection(normal, viewDir);

    // 使用Z-buffer计算深度来模拟透光效果
    float thickness = ComputeThickness(worldPos);

    // 加入透光效果（厚度越大，透光效果越强）
    color *= thickness;

    // 加入环境光遮蔽
    color *= aoFactor;

    // 添加发光效果
    color += emissionColor;

    // 输出最终颜色
    FragColor = vec4(color, 1.0);
}
