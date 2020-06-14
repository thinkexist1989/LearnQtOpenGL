#version 460 core
layout (location=0) in vec3 aPos;

out vec4 vertexColor; //for fragment shader's color output
void main(void)
{
    gl_Position = vec4(aPos.xyz, 1.0);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); //dark red
}
