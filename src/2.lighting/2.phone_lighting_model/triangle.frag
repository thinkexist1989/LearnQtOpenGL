#version 460 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;

//in vec2 texCoord;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

void main(void)
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0f);
//    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//    FragColor = vertexColor;
//    FragColor = mix(texture2D(texture1, texCoord),texture2D(texture2, texCoord), 0.2);
}
