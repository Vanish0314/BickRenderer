#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform vec4 ourColor;
uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
    vec4 texColor0 = texture(Texture0, texCoord);
    vec4 texColor1 = texture(Texture1, texCoord);
    FragColor = texColor0 * texColor1 * ourColor;
}
