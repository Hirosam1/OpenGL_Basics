#version 330 core
//We declare an output, we only need one
out vec4 FragColor;

//uniform vec4 ourColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    //This defines the final color
    //FragColor = vec4(ourColor,1.0);
    //build in function that does the sampling
    vec4 texColor = vec4(texture(texture1,TexCoord));
    
    if (texColor.a < 0.4)
        discard;
    FragColor = texColor * vec4(ourColor,1);
} 