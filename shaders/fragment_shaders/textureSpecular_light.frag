#version 330 core
//We declare an output, we only need one
out vec4 FragColor;

in vec2 TexCoord;

in vec3 aNormal;
in vec3 FragPos;
in vec3 LightPos;

struct Material{
    sampler2D texture1;
    sampler2D specular;
    vec3 ambient;
    vec3 diffuse;
    float shininess;
};

struct Light{
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 lightColor;
uniform Material material;
uniform Light light;


void main()
{
    vec4 texColor = vec4(texture(material.texture1,TexCoord));
    vec4 specColor = vec4(texture(material.specular,TexCoord));
    
    vec3 norm = normalize(aNormal);
    //Difuse
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm,lightDir),0);
    vec3 diffuse = (diff * material.diffuse) * vec3(texColor);

    //Specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(specColor));  

    vec3 ambient = light.ambient * vec3(texColor) * material.ambient;
    vec3 result =(diffuse + ambient + specular);
    
    if (texColor.a < 0.5)
        discard;

    FragColor = vec4(result,1);
} 