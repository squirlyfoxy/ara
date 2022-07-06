#version 430 core
layout (location = 0) out vec4 color;
layout (location = 1) out int color2;

uniform vec3 u_color;
uniform int u_uid = -1;

uniform sampler2D u_texture;

void main()
{
    color = texture(u_texture, gl_FragCoord.xy);
    color2 = u_uid;
}
