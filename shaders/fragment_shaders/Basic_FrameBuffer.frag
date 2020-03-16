#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D screenTex;

void main(){
    FragColor =  texture(screenTex,TexCoord);
    //FragColor = vec4(0.3,1,1,1);
}