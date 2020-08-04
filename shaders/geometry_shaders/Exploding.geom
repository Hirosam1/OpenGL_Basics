#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT{
    vec2 TexCoord;
    vec3 aNormal;
    vec3 FragPos;
} gm_in[];

out VS_OUT{
    vec2 TexCoord;
    vec3 aNormal;
    vec3 FragPos;
} gm_out;

uniform float time;

vec3 GetNormal(){
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal){
    float magnitude = 1.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; 
    return position + vec4(direction.xy,0,0.0);
}

void main(){
    //vec3 normal = GetNormal();
    gl_Position = explode(gl_in[0].gl_Position,gm_in[0].aNormal);
    //gl_Position = explode(gl_in[0].gl_Position,normal);
    //gl_Position = gl_in[0].gl_Position;
    gm_out.TexCoord = gm_in[0].TexCoord;
    gm_out.aNormal = gm_in[0].aNormal;
    gm_out.FragPos = gm_in[0].FragPos;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position,gm_in[1].aNormal);
    //gl_Position = explode(gl_in[1].gl_Position,normal);
    //gl_Position = gl_in[1].gl_Position;
    gm_out.TexCoord = gm_in[1].TexCoord;
    gm_out.aNormal = gm_in[1].aNormal;
    gm_out.FragPos = gm_in[1].FragPos;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position,gm_in[2].aNormal);
    //gl_Position = explode(gl_in[2].gl_Position,normal);
    //gl_Position = gl_in[2].gl_Position;
    gm_out.TexCoord = gm_in[2].TexCoord;
    gm_out.aNormal = gm_in[2].aNormal;
    gm_out.FragPos = gm_in[2].FragPos;
    EmitVertex();
    EndPrimitive();
}