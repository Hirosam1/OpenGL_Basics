#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 aTexCoord;


layout(std140) uniform Camera{
                        //base alignment    //aligned offset
    mat4 Projection;    //16                //0
    mat4 View;          //16                //16
                        //32
};

uniform mat4 Model;
out vec3 global_pos;
out VS_OUT{
    vec2 TexCoord;
    vec3 aNormal;
    vec3 FragPos;
} vs_out;

const float MAGNETUDE = .5;
uniform float time;

vec4 Distort(vec4 position){
    vec3 direction =  vs_out.aNormal * (sin(time + aPos.x + aPos.y +aPos.z )/3+0.3)* MAGNETUDE;
    return position + vec4(direction.xy,0,0);

}

void main()
{
    vs_out.aNormal = mat3(transpose(inverse(View * Model))) * normal; 
    vs_out.FragPos = vec3(View * Model * vec4(aPos,1.0));
    gl_Position = Distort(Projection * vec4(vs_out.FragPos,1.0));
    vs_out.TexCoord = aTexCoord;
}