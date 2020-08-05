#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT{
    vec2 TexCoord;
    vec3 aNormal;
    vec3 FragPos;
} gm_in[];

in vec3 global_pos[];

out VS_OUT{
    vec2 TexCoord;
    vec3 aNormal;
    vec3 FragPos;
} gm_out;

uniform float time;
const float MAGNETUDE = .5;

vec4 Distort(vec4 position, int index){
    vec3 direction =  gm_in[index].aNormal * (sin(time + global_pos[index].x + global_pos[index].y +global_pos[index].z )/3+0.3)* MAGNETUDE;
    gm_out.TexCoord = gm_in[index].TexCoord;
    gm_out.aNormal = gm_in[index].aNormal;
    gm_out.FragPos = gm_in[index].FragPos;
    return position + vec4(direction.xy,0,0);

}

void main(){
    gl_Position = Distort(gl_in[0].gl_Position,0);
    EmitVertex();
    gl_Position = Distort(gl_in[1].gl_Position,1);
    EmitVertex();
    gl_Position = Distort(gl_in[2].gl_Position,2);
    EmitVertex();
    EndPrimitive();
}