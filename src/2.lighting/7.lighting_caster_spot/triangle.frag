#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

in vec2 TexCoords;

uniform vec3 viewPos;

uniform vec3 lightColor;
//uniform vec3 objectColor;

struct Material {
    vec3 ambient; //环境光几乎在任何情况下都和漫反射颜色一致

    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;

    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;

void main(void)
{

    //ambient 环境光
    //    vec3 ambient = light.ambient * material.ambient;
    vec3 ambient = light.ambient * texture2D(material.diffuse, TexCoords).rgb;

    //diffuse 漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    //    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(norm, lightDir), 0.0);
    //    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    vec3 diffuse = light.diffuse * diff * texture2D(material.diffuse, TexCoords).rgb;

    //specular 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); //求解镜面光反射，reflect函数要求第一个向量为从广源指向片段位置的向量，因此将lightDir取反

    float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess); //32次幂是反光度， 反光度越高，发射光能力越强，散射越少
    vec3 specular = light.specular * spec * texture2D(material.specular, TexCoords).rgb;

    vec3 emission = texture2D(material.emission, TexCoords).rgb;

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    //    vec3 result = ambient + diffuse + specular + emission;


    float theta = dot(lightDir, normalize(-light.direction)); //保存的是余弦值
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta-light.outerCutOff)/epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0f);
}
