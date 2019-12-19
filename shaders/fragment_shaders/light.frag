#version 330 core
out vec4 FragColor;

in vec3 aNormal;
in vec3 FragPos;
in vec3 LightPos;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = material.ambient * light.ambient;

    vec3 norm = normalize(aNormal);
    //Difuse
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm,lightDir),0);
    vec3 diffuse = (diff * material.diffuse) * light.diffuse;

    //Specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}