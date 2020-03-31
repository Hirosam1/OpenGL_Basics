#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 aNormal;

uniform samplerCube skybox;
uniform mat4 View;
const float ratio = 1.0/1.1;

void main() {
    vec3 I      = normalize(FragPos);
    vec3 viewR  = refract(I, normalize(aNormal),ratio);
    vec3 worldR = inverse(mat3(View)) * viewR;
    FragColor   = vec4(texture(skybox, worldR).rgb, 1.0);
}