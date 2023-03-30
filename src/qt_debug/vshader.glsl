#version 330 core
// Positions/Coordinates
layout (location = 0) in vec3 aPos;

vec3 color = vec3(1,1,1);
out vec4 f_color;
//uniform mat4 model;
uniform mat4 camMatrix;
vec4 mvp_vec;

void main()
{
    mvp_vec = camMatrix * vec4(aPos, 1);
    gl_Position = mvp_vec;
    gl_PointSize = 2.0;
    f_color = vec4(color, 1.0);
}
