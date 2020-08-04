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
//uniform mat4 View;
//uniform mat4 Projection;

out VS_OUT{
    vec2 TexCoord;
    vec3 aNormal;
    vec3 FragPos;
} vs_out;

void main()
{
    vs_out.aNormal = mat3(transpose(inverse(View * Model))) * normal; 
    vs_out.FragPos = vec3(View * Model * vec4(aPos,1.0));
    gl_Position = Projection * vec4(vs_out.FragPos,1.0);
    vs_out.TexCoord = aTexCoord;
}