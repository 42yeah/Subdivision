#version 330 core

// Just some fake lighting

in vec3 pos;
in vec3 normal;

out vec4 color;


void main() {
    color = vec4(normal, 0);
}
