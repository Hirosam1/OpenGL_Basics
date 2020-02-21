#version 330 core
//We declare an output, we only need one
out vec4 FragColor;

in vec2 TexCoord;

in vec3 aNormal;
in vec3 FragPos;
in vec3 LightPos;
in vec3 LightDir;

struct Material{
    sampler2D texture1;
    sampler2D specular;
    vec3 ambient;
    vec3 diffuse;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};


uniform vec3 lightColor;
uniform Material material;
uniform Light light;


void main()
{
    vec4 texColor = vec4(texture(material.texture1,TexCoord));
    vec4 specColor = vec4(texture(material.specular,TexCoord));

    vec3 norm = normalize(aNormal);
    float distance = length(LightPos - FragPos);
    float attenuation = 1.0/(light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));
    vec3 result = vec3(0);
    //vec3  lightDir = normalize(-LightDir);
    vec3 lightDir = normalize(LightPos - FragPos);
    //Inner cone
    float theta = dot(lightDir,normalize(-LightDir));

    //calculates intensity
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff)/epsilon,0.0,1.0);

    //Ambient
    vec3 ambient = light.ambient * vec3(texColor) * material.ambient;
    ambient *= attenuation * intensity;
    //Difuse
    float diff = max(dot(norm,lightDir),0);
    vec3 diffuse = (diff * material.diffuse) * vec3(texColor) * light.diffuse;
    diffuse *= attenuation * intensity;

    //Specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(specColor));
    specular *= attenuation * intensity;

    result =(diffuse + ambient + specular);
    
    
    if (texColor.a < 0.5)
        discard;

    FragColor = vec4(result,1);
} 