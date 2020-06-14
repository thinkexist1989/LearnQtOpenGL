#version 460 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;

out vec3 vertexColor; //for fragment shader's color output

void main(void)
{
    gl_Position = vec4(aPos.xyz, 1.0);
    vertexColor = aColor; //dark red
}
