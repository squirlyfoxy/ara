#version 430 core

uniform vec3 u_color;

// Scale and resolution
uniform float u_scale;
uniform float u_resolution;

out vec4 FragColor;

// adapted from https://thebookofshaders.com/edit.php#10/ikeda-simple-grid.frag
 
float grid(vec2 st, float res)
{
  vec2 grid = fract(st*res);
  return (step(res,grid.x) * step(res,grid.y));
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution;
    float grid_value = grid(st, u_scale);
    FragColor = vec4(u_color, grid_value);
}
