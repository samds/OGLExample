#version 330 core

layout(location = 0) in vec3 position;

void main() {
    gl_Position.xyz = position;
    gl_Position.w = 1.0;
    // or
    // gl_Position = vec4(position,1.0);
}