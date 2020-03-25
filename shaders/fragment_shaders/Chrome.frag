#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 aNormal;

uniform samplerCube skybox;
uniform mat4 View;

void main() {
    vec3 I      = normalize(FragPos);
    vec3 viewR  = reflect(I, normalize(aNormal));
    vec3 worldR = inverse(mat3(View)) * viewR;
    FragColor   = vec4(texture(skybox, worldR).rgb, 1.0);
}