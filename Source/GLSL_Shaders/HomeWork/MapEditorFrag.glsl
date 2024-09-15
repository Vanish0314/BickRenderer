#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;

uniform sampler2D controlMap;

void main()
{
    // 从控制图中获取颜色
    vec4 control = texture(controlMap, texCoord);
    
    // 计算控制的总和并避免除零错误
    float m = max(control.x + control.y + control.z, 0.01);
    
    // 更新控制为 vec4 并保留 w 分量
    control = vec4
    (
        control.x / m,
        control.y / m,
        control.z / m,
        control.w // 保留 original w 分量
    );

    vec4 color = vec4(0.0);

    // 根据控制分量混合不同的纹理
    color += texture(Texture0, texCoord) * control.x;
    color += texture(Texture1, texCoord) * control.y;
    color += texture(Texture2, texCoord) * control.z;
    
    // 根据控制分量混合最后一种纹理
    color = mix(color, texture(Texture3, texCoord),1 - control.w);

    // 输出构建的颜色
    FragColor = color;
}
