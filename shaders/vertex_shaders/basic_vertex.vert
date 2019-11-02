#version 330 core
layout (location = 0) in vec3 aPos;
layout (location =1) in vec3 aColor;

out vec3 ourColor;

//Usually you would transform the input into coordinates that fall within OpenGL's visible region
void main()
{
    //the predifined gl_Position variable will be used as an output of this shader
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    ourColor = aColor;
}