#version 430 core
layout (location = 0) out vec4 color;
layout (location = 1) out int color2;

in vec2 TexCoords;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
    color2 = -1; // Not selectable
}  