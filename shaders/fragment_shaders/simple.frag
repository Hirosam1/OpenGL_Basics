#version 330 core
#define MAX_POINT_LIGHTS 4
//We declare an output, we only need one
out vec4 FragColor;

in vec2 TexCoord;


struct Material{
    bool has_TexDiffuse;
    sampler2D texture_diffuse1;
    vec3 diffuse;
};

uniform Material material;

void main()
{
    if(material.has_TexDiffuse)
        FragColor = vec4(vec3(texture(material.texture_diffuse1,TexCoord)) * material.diffuse,1);
    else
        FragColor = vec4(material.diffuse,1);

} 