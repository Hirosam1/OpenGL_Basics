#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 normal;

struct Light{
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 lightPos;

out vec2 TexCoord;
out vec3 LightPos;
out vec3 aNormal;
out vec3 FragPos;


//Usually you would transform the input into coordinates that fall within OpenGL's visible region
void main()
{
    //the predifined gl_Position variable will be used as an output of this shader
   
    
    aNormal = mat3(transpose(inverse(View * Model))) * normal; 
    LightPos = vec3(View * vec4(light.position,1.0));
    FragPos = vec3(View * Model * vec4(aPos,1.0));
    gl_Position = Projection * vec4(FragPos,1.0);
    TexCoord = aTexCoord;
}