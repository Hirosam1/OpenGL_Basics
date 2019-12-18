#version 330 core
//We declare an output, we only need one
out vec4 FragColor;

in vec2 TexCoord;

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


uniform sampler2D texture1;
uniform vec3 lightColor;
uniform Material material;
uniform Light light;


void main()
{
    vec3 ambient = material.ambient * light.ambient;

    vec3 norm = normalize(aNormal);
    //Difuse
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm,lightDir),0);
    vec3 diffuse = (diff * material.ambient) * light.diffuse;

    //Specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0), material.shininess);
    vec3 specular = light.specular * (spec * material.ambient);  

    vec4 texColor = vec4(texture(texture1,TexCoord));

    vec3 result =(diffuse + ambient + specular) * (vec3(texColor));
    

    
    
    if (texColor.a < 0.1)
        discard;

    FragColor = vec4(result,1);
} 