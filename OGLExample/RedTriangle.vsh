#version 330 core

layout(location = 0) in vec3 vertex;

void main() {
    gl_Position.xyz = vertex;
    gl_Position.w = 1.0;
    // or
    // gl_Position = vec4(vertex,1.0);
}