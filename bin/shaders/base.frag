#version 430 core
layout (location = 0) out vec4 color;
layout (location = 1) out int color2;

uniform vec3 u_color;
uniform int u_uid = -1;

void main()
{
    color = vec4(u_color, 1.0);
    color2 = u_uid;
}
