#version 330 core

// Just some fake lighting

in vec3 pos;
in vec3 normal;

out vec4 color;


void main() {
    vec3 objectColor = vec3(1.0);
 
    color = vec4(normal, 0);
}
