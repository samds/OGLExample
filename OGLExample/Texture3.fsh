#version 150

in vec2 textureCoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
    vec2 flippedTextureCoord = vec2(textureCoord.x, 1.0 - textureCoord.y);
    outColor = texture(tex, flippedTextureCoord);// * vec4(color, 1.0);
}