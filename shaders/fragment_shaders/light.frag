#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;

in vec3 ourColor;

void main()
{
    FragColor = vec4(lightColor * ourColor, 1.0);
}