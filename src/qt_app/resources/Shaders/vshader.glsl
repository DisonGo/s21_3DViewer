#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 f_color;

uniform vec3 aColor;
uniform float aPointSize;

uniform mat4 camMatrix;
uniform mat4 model;

vec4 mvp_vec;

uniform bool dashed;
uniform vec2 dash_pattern;

out float pattern_value;
float rnd(float i) {
        return mod(4000.*sin(23464.345*i+45.345),1.);
}
void main()
{
    mvp_vec = camMatrix * model * vec4(aPos, 1);
    gl_Position = mvp_vec;
    gl_PointSize = 1;
    f_color = vec4(rnd(aPos.x),rnd(aPos.y),rnd(aPos.z), 1.0);

    if (dashed) {
//        float length = length(vec2(fwidth(gl_Position.xy)));
//        pattern_value = mod(length, dash_pattern.x + dash_pattern.y);
    }
}
