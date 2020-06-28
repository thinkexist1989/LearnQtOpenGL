#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

in vec2 TexCoords;

uniform vec3 viewPos;

uniform vec3 lightColor;
//uniform vec3 objectColor;

struct Material {
//    vec3 ambient; //环境光几乎在任何情况下都和漫反射颜色一致，因此只需要使用diffuse的纹理

    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;

    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform DirLight dirLight;

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(void)
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    //定向光
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    //点光源
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }
    //聚光
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    //计算光线方向
    vec3 lightDir = normalize(-light.direction);
    //计算漫反射
    float diff = max(dot(lightDir, normal), 0.0);
    //
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));

    return (ambient + diffuse + specular);

}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(lightDir, normal), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation; //点光源对环境光也衰减
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    //计算光线方向
    vec3 lightDir = normalize(light.position - fragPos);

    //计算漫反射
    float diff = max(dot(lightDir, normal), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic *( distance * distance));

    float epsilon = light.cutOff - light.outerCutOff;
    float theta = dot(lightDir, normalize(-light.direction));
    float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}
