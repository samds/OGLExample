#version 150

in vec2 inPosition;
in vec3 inColor;

out vec3 color; // forwarded to the fragment shader program


void main()
{
    color = inColor;
    gl_Position = vec4(inPosition, 0.0, 1.0);
}