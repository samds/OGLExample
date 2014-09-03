#version 150

in vec2 inPosition;
in vec3 inColor;
in vec2 inTextureCoord;

out vec3 color; // forwarded to the fragment shader program
out vec2 textureCoord;


void main()
{
    color = inColor;
    textureCoord = inTextureCoord;
    gl_Position = vec4(inPosition, 0.0, 1.0);
}