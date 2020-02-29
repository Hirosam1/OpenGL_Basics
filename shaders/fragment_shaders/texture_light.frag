#version 330 core
//We declare an output, we only need one
out vec4 FragColor;
#define MAX_POINT_LIGHTS 4
uniform int n_point_lights;

in vec2 TexCoord;

in vec3 aNormal;
in vec3 FragPos;

struct Material{
    sampler2D texture1;
    sampler2D specular;
    vec3 ambient;
    vec3 diffuse;
    float shininess;
};

struct DirLight{
    vec3 directionVS;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 positionVS;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
  
};

struct SpotLight{
    vec3 positionVS;
    vec3 directionVS;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

uniform Material material;

vec3 CalcDirLight(DirLight light,vec3 normal){
    vec3 viewDir = normalize(-FragPos);
    vec3 lightDir = normalize(-light.directionVS);
    //Ambient
    vec3 ambient = light.ambient * vec3(texture(material.texture1,TexCoord)) * material.ambient;
    //Difuse
    float diff = max(dot(normal,lightDir),0);
    vec3 diffuse = (diff * material.diffuse) * vec3(texture(material.texture1,TexCoord)) * light.diffuse;
    //Specular
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0), material.shininess);
    vec3 specular = light.specular * spec;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light,vec3 normal, vec3 fragPos){
    vec3 viewDir = normalize(-FragPos);
    vec3 lightDir = normalize(light.positionVS - fragPos);
    float distance = length(light.positionVS - FragPos);
    float attenuation = 1.0/(light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));
    //Ambient
    vec3 ambient = light.ambient * vec3(texture(material.texture1,TexCoord)) * material.ambient;
    ambient *= attenuation;
    //Difuse
    float diff = max(dot(normal,lightDir),0);
    vec3 diffuse = (diff * material.diffuse) * vec3(texture(material.texture1,TexCoord)) * light.diffuse;
    diffuse *= attenuation;
    //Specular
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0), material.shininess);
    vec3 specular = light.specular * spec;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos){
    vec3 viewDir = normalize(-fragPos);
    float distance = length(light.positionVS - fragPos);
    float attenuation = 1.0/(light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));
    vec3 lightDir = normalize(light.positionVS - fragPos);
    //Inner cone
    float theta = dot(lightDir,normalize(-light.directionVS));
    //calculates intensity
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff)/epsilon,0.0,1.0);
    //Ambient
    vec3 ambient = light.ambient * vec3(texture(material.texture1,TexCoord)) * material.ambient;
    ambient *= attenuation * intensity;
    //Difuse
    float diff = max(dot(normal,lightDir),0);
    vec3 diffuse = (diff * material.diffuse) * vec3(texture(material.texture1,TexCoord)) * light.diffuse;
    diffuse *= attenuation * intensity;
    //Specular
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0), material.shininess);
    vec3 specular = light.specular * spec;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform DirLight dirLight;
uniform SpotLight spotLight;

uniform int hasSpotLight;

void main()
{
    vec4 texColor = vec4(texture(material.texture1,TexCoord));

    vec3 norm = normalize(aNormal);
    vec3 result = CalcDirLight(dirLight, norm);

    if (hasSpotLight > 0 ){
        result += CalcSpotLight(spotLight, norm, FragPos);
    }
    for(int i = 0; i < n_point_lights && i < MAX_POINT_LIGHTS; i++){
        result += CalcPointLight(pointLights[i], norm, FragPos);
    }

    
    if (texColor.a < 0.5)
        discard;

    FragColor = vec4(result,1);
} 