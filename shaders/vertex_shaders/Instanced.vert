#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 aOffset;


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

void main()
{
    float offset = 0.5;
    vec3 transPos = aPos * ((100 - gl_InstanceID) / 100.0) + vec3(aOffset, 0.0);
    vs_out.aNormal = mat3(transpose(inverse(View * Model))) * normal; 
    vs_out.FragPos = vec3(View * Model * vec4(transPos,1.0));
    gl_Position = Projection * vec4(vs_out.FragPos,1.0);

    global_pos = aPos;
    vs_out.TexCoord = aTexCoord;
}
