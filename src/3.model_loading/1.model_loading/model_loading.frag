#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

sampler2D texture_diffuse1;

void main()
{
    FragColor = texture2D(texture_diffuse1, TexCoords);
}