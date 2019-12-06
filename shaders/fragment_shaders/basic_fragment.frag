#version 330 core
//We declare an output, we only need one
out vec4 FragColor;

uniform vec3 aColor;

void main()
{
    //This defines the final color
    FragColor = vec4(aColor,1.0);
} 