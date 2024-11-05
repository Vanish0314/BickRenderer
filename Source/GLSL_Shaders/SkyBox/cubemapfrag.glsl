#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{   
    vec3 color = texture(skybox,TexCoords).xyz;
    FragColor = vec4(color,1);
}