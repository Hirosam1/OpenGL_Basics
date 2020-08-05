#version 330 core
layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

const float MAGNITUDE = 0.4;
in VS_OUT{
    vec2 TexCoord;
    vec3 aNormal;
    vec3 FragPos;
} gm_in[];

layout(std140) uniform Camera{
                        //base alignment    //aligned offset
    mat4 Projection;    //16                //0
    mat4 View;          //16                //16
                        //32
};
out vec3 color;
out VS_OUT{
    vec2 TexCoord;
    vec3 aNormal;
    vec3 FragPos;
} gm_out;

uniform float time;

void GenerateLine(int index){
    gl_Position = gl_in[index].gl_Position;
    color = vec3(1);
    EmitVertex();
    gl_Position = (gl_in[index].gl_Position + (Projection * vec4(gm_in[index].aNormal,0.0)) * MAGNITUDE);
    color = vec3(0.98,0.28,0.125);
    EmitVertex();
    EndPrimitive();
}

void GenarateLineCenter(){
    vec4 center =  (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3;
    gl_Position =center;
    color = vec3(1);
    EmitVertex();
    gl_Position =  (center + (Projection * vec4(gm_in[0].aNormal,0.0)) * MAGNITUDE);
    color = vec3(0.98,0.28,0.125);
    EmitVertex();
    EndPrimitive();
}

void main(){
    /*
    GenerateLine(0);
    GenerateLine(1);
    GenerateLine(2);*/
    GenarateLineCenter();
}