#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;

out vec3 ourColor;
out vec2 TexCoord;

//Usually you would transform the input into coordinates that fall within OpenGL's visible region
void main()
{
    //the predifined gl_Position variable will be used as an output of this shader
    gl_Position = transform * vec4(aPos,1.0);

    ourColor = aColor;
    TexCoord = aTexCoord;
}