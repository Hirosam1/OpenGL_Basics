#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

struct Material{
    bool has_TexDiffuse;
    sampler2D texture_diffuse1;
};

uniform Material material;

void main(){
    FragColor = vec4(0);
    if(material.has_TexDiffuse){
        FragColor = texture(material.texture_diffuse1,TexCoord);
    }

}