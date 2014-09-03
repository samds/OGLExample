#version 150

//in vec3 color;
in vec2 textureCoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
    outColor = texture(tex, textureCoord);// * vec4(color, 1.0);
}