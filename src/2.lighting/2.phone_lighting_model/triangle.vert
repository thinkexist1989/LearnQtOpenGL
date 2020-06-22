#version 460 core
layout (location=0) in vec3 aPos;
//layout (location=1) in vec2 aTexCoord;

out vec3 ourColor; //for fragment shader's color output
//out vec2 texCoord; // texture coordinate

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main(void)
{
    gl_Position = projection*view*model*vec4(aPos.xyz, 1.0);
//    texCoord = aTexCoord;
}
