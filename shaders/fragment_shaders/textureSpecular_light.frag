#version 330 core
#define MAX_POINT_LIGHTS 4
//We declare an output, we only need one
out vec4 FragColor;
uniform int n_point_lights;

in vec2 TexCoord;

in vec3 aNormal;
in vec3 FragPos;

struct Material{
    uniform sampler2D texture_diffuse1;
    uniform sampler2D texture_diffuse2;
    uniform sampler2D texture_diffuse3;
    uniform sampler2D texture_specular1;
    uniform sampler2D texture_specular2;
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
    vec3 specular = light.specular * (spec * vec3(texture(material.specular,TexCoord)));

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light,vec3 normal, vec3 fragPos){
    vec3 viewDir = normalize(-FragPos);
    vec3 lightDir = normalize(light.positionVS - fragPos);
    float distance = length(light.positionVS - FragPos);
    float constant = clamp(light.constant,0.0,1.0);

    if(light.linear  < 0.01){
        discard;
    }

    float attenuation = 1.0/(constant + (light.linear * distance) + (light.quadratic * (distance * distance)));
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
    vec3 specular = light.specular * (spec * vec3(texture(material.specular,TexCoord)));
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
    ambient *= intensity * attenuation;
    //Difuse
    float diff = max(dot(normal,lightDir),0);
    vec3 diffuse = (diff * material.diffuse) * vec3(texture(material.texture1,TexCoord)) * light.diffuse;
    diffuse *=  intensity * attenuation;
    //Specular
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular,TexCoord)));
    specular *=  intensity * attenuation;

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