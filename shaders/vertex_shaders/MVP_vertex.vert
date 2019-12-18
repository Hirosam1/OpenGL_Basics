#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;

struct Light{
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform Light light;

out vec3 aNormal;
out vec3 FragPos;
out vec3 LightPos;

//Usually you would transform the input into coordinates that fall within OpenGL's visible region
void main()
{

    aNormal = mat3(transpose(inverse(View * Model))) * normal; 
    FragPos = vec3(View * Model * vec4(aPos,1.0));
    gl_Position =  Projection  * vec4(FragPos,1.0);
    LightPos = vec3(View * vec4(light.position,1.0));
}