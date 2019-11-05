#version 330 core
//We declare an output, we only need one
out vec4 FragColor;

//uniform vec4 ourColor;
in vec3 ourColor;
in vec2 TexCoord;
in vec4 gl_FragCoord;

uniform sampler2D texture1;
vec2 SineWave(vec2 p){
    float pi = 3.14159;
    float A = 0.15;
    float w = 10.0 * pi;
    float t = 30.0*pi/180.0;    
    float y = sin( w*p.x + t) * A;
    return vec2(p.y,p.y+y);
}

void main()
{
    //build in function that does the sampling
    vec4 texColor = vec4(texture(texture1,SineWave(TexCoord.xy)));
    
    if (texColor.a < 0.4)
        discard;
    
    FragColor = texColor * vec4(ourColor,1);
    
    
} 