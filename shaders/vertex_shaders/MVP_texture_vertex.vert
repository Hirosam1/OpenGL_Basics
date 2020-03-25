#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 TexCoord;
out vec3 aNormal;
out vec3 FragPos;

void main()
{
    aNormal = mat3(transpose(inverse(View * Model))) * normal; 
    FragPos = vec3(View * Model * vec4(aPos,1.0));
    gl_Position = Projection * vec4(FragPos,1.0);
    TexCoord = aTexCoord;
}