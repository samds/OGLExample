#version 150

in vec2 inPosition;
in vec2 inTextureCoord;

out vec2 textureCoord;


void main()
{
    textureCoord = inTextureCoord;
    gl_Position = vec4(inPosition, 0.0, 1.0);
}
