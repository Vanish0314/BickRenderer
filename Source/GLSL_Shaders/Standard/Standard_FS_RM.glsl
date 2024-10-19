#version 330 core

in vec2 uv;
in vec3 normal;

uniform sampler2D albedo;
uniform sampler2D metallic;
uniform sampler2D roughness;
uniform sampler2D emission;
uniform sampler2D ao;

out vec4 FragColor;

void main ()
{
    vec4 color = texture(albedo, uv);
    vec3 metallic_value = texture(metallic, uv).rgb;
    float roughness_value = texture(roughness, uv).r;    
    vec3 emission_value = texture(emission, uv).rgb;
    float ao_value = texture(ao, uv).r;
    
    vec3 N = normalize(normal);
    vec3 V = normalize(-vec3(0,0,1));
    vec3 L = normalize(vec3(1,1,1));
    
    vec3 H = normalize(L + V);
    float NdotL = max(dot(N, L), 0.0);
    float NdotH = max(dot(N, H), 0.0);
    float VdotH = max(dot(V, H), 0.0);
    
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, color.rgb, metallic_value.r);
    
    float alpha = roughness_value * roughness_value;
    vec3 F = F0 + (1.0 - F0) * pow(1.0 - VdotH, 5.0);
    
    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic_value.r;
    
    vec3 diffuse = color.rgb * (kD * ao_value + emission_value);
    vec3 specular = color.rgb * (kS * pow(NdotH, 5.0) * ao_value);
    
    vec3 color_final = diffuse + specular;
    
    FragColor = vec4(color_final, 1.0);
}

