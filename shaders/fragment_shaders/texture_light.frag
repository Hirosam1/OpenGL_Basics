#version 330 core
//We declare an output, we only need one
out vec4 FragColor;

//uniform vec4 ourColor;
in vec3 ourColor;
in vec2 TexCoord;

in vec3 aNormal;
in vec3 FragPos;
in vec3 LightPos;


uniform sampler2D texture1;
uniform vec3 lightColor;


void main()
{
    vec3 norm = normalize(aNormal);
    //Difuse
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm,lightDir),0);
    vec3 diffuse = diff * lightColor;
    //Specular
    float specularStrengt = 0.5;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0),190);
    vec3 specular = specularStrengt * spec * lightColor;

    float ambientStrenght = 0.4;
    vec3 ambient = ambientStrenght * lightColor;

    vec4 texColor = vec4(texture(texture1,TexCoord));

    vec3 result =(diffuse + ambient + specular) * (vec3(texColor) * ourColor);
    

    
    
    if (texColor.a < 0.1)
        discard;

    FragColor = vec4(result,1);
} 