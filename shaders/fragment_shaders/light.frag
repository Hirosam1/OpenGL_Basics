#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 aColor;

in vec3 aNormal;
in vec3 FragPos;
in vec3 LightPos;

void main()
{
    vec3 norm = normalize(aNormal);
    //Difuse
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm,lightDir),0);
    vec3 diffuse = diff * lightColor;

    //Specular
    float specularStrengt = 0.7;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0),190);
    vec3 specular = specularStrengt * spec * lightColor;
    

    float ambientStrenght = 0.2;
    
    vec3 ambient = ambientStrenght * lightColor;
    vec3 result =(diffuse + ambient + specular) * aColor;
    FragColor = vec4(result, 1.0);
}