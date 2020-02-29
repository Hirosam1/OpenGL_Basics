#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform vec3 LampColor;

void main()
{
    FragColor = vec4(LampColor,1.0);
}