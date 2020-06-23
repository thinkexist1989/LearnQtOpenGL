#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main(void)
{
    //ambient 环境光
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    //diffuse 漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos-FragPos);

    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diff * lightColor;

    //specular 镜面光
    float specularStrength = 0.5; //镜面强度 specular intensity
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); //求解镜面光反射，reflect函数要求第一个向量为从广源指向片段位置的向量，因此将lightDir取反

    float spec = pow(max(dot(reflectDir, viewDir), 0.0), 32); //32次幂是反光度， 反光度越高，发射光能力越强，散射越少
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0f);
}
