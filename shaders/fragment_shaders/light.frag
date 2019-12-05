#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 ourColor;
in vec3 aNormal;
in vec3 FragPos;

void main()
{
    vec3 norm = normalize(aNormal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm,lightDir),0);
    vec3 diffuse = diff * lightColor;
    float ambientStrenght = 0.155;
    
    vec3 ambient = ambientStrenght * lightColor;
    vec3 result =(diff + ambient) * ourColor;
    FragColor = vec4(result, 1.0);
}