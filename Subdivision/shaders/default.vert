#version 330 core

uniform mat4 view;
uniform mat4 perspective;

layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = perspective * view * vec4(aPos, 1.0);
}
