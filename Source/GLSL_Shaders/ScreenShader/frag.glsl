#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{ 
    // FragColor = vec4(1-vec3(texture(screenTexture, TexCoords)), 1.0);
    FragColor = vec4(0.4,1.0,0.2,1.0);
}