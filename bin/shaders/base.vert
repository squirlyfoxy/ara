#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 proj = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);

out vec2 TexCoord;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}