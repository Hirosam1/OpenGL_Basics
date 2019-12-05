#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
//layout (location = 2) in vec2 aTexCoord;

uniform mat4 Model;
uniform mat4 VP;
uniform vec3 aColor;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 aNormal;
out vec3 FragPos;

//Usually you would transform the input into coordinates that fall within OpenGL's visible region
void main()
{
    

    ourColor = aColor;
    aNormal = mat3(transpose(inverse(Model))) * normal; 
    FragPos = vec3(Model  * vec4(aPos,1.0));
    gl_Position =  VP * Model * vec4(aPos,1.0);
}