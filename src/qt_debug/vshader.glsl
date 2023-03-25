#version 330 core
// Positions/Coordinates
layout (location = 0) in vec3 aPos;

vec3 color = vec3(1,0,0);
out vec4 f_color;

uniform vec3 translateVec;
uniform float scale;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

//vec4 mvp_vec;
void main()
{
    // Calculate vertex position in screen space
//    mvp_vec = model * view * proj * vec4(aPos, 1) * scale;
    vec3 translated_pos = aPos + translateVec;
    gl_Position = vec4(translated_pos, scale);
    gl_PointSize = 10.0;
    f_color = vec4(color, 1.0);
}
