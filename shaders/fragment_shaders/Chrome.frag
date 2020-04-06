#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 aNormal;

uniform samplerCube skybox;
uniform mat4 View;

const vec3 color = vec3(0.7,0.2,0.9);
const float ref_factor = 0.4;

void main() {

    vec3 I      = normalize(FragPos);
    vec3 viewR  = reflect(I, normalize(aNormal));
    vec3 worldR = inverse(mat3(View)) * viewR;
    vec3 ref_color = texture(skybox, worldR).rgb * ref_factor;
    vec3 color_part = color * (1-ref_factor);
    FragColor   = vec4(ref_color + color_part, 1.0);
}