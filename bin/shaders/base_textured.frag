#version 430 core
layout (location = 0) out vec4 color;
layout (location = 1) out int color2;

uniform int u_uid = -1;

uniform sampler2D u_texture;
in vec2 TexCoord;

void main()
{
    color = texture(u_texture, TexCoord);
    color2 = u_uid;
}
