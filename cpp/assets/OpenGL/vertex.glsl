#version 330 core

layout (location = 0) in vec3 aPos;      // position
layout (location = 1) in vec3 aNormal;   // normale (optionnel)
layout (location = 2) in vec2 aTexCoord; // UV (optionnel)

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

out float fragDepth; // on envoie la profondeur au fragment shader

void main()
{
    // Position monde
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Normale transformée
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // UV
    TexCoord = aTexCoord;

    vec4 viewPos = view * vec4(FragPos, 1.0);
    fragDepth = -viewPos.z; // distance devant la caméra

    // Position finale
    gl_Position = projection * viewPos;
}