#version 330 core
#define MAX_POINT_LIGHTS 4
//We declare an output, we only need one
out vec4 FragColor;

in vec2 TexCoord;


struct Material{
    sampler2D texture_diffuse1;
};

uniform Material material;

void main()
{

    FragColor = texture(material.texture_diffuse1,TexCoord);

} 