#version 330 core
//We declare an output, we only need one
out vec4 FragColor;

//uniform vec4 ourColor;
in vec3 ourColor;

void main()
{
    //This defines the final color
    FragColor = vec4(ourColor,1.0);
} 