#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 shit;
layout(location = 2) in vec3 shit2;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 FragPos;


//Usually you would transform the input into coordinates that fall within OpenGL's visible region
void main()
{

    FragPos = vec3(View * Model * vec4(aPos,1.0));
    gl_Position =  Projection  * vec4(FragPos,1.0);
}