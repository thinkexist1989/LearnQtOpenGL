#version 460 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aTexCoord;

out vec3 ourColor; //for fragment shader's color output
out vec2 texCoord; // texture coordinate
void main(void)
{
    gl_Position = vec4(aPos.xyz, 1.0);
    ourColor = aColor;
    texCoord = aTexCoord;
}
