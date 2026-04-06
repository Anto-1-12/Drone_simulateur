#version 330 core
in float fragDepth;
out vec4 FragColor;

uniform float nearPlane; // 0.1
uniform float farPlane;  // 100.0

void main()
{
    // normaliser la profondeur entre 0 et 1
    float depth = (fragDepth - nearPlane) / (farPlane - nearPlane);
    depth = clamp(depth, 0.0, 1.0);

    // plus loin = plus sombre
    FragColor = vec4(vec3(1.0 - depth), 1.0);
}