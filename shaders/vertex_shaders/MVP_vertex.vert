#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 lightPos;

//uniform vec3 lightPos;

out vec3 LightPos;
out vec3 aNormal;
out vec3 FragPos;

//Usually you would transform the input into coordinates that fall within OpenGL's visible region
void main()
{

    aNormal = mat3(transpose(inverse(View * Model))) * normal; 
    FragPos = vec3(View * Model * vec4(aPos,1.0));
    gl_Position =  Projection  * vec4(FragPos,1.0);
    LightPos = vec3(View * vec4(lightPos,1.0));
}