#version 330 core
layout(location = 0) in vec3 aPos;

flat out vec4 f_color;
out vec4 vClipPos;

uniform mat4 camMatrix;
uniform mat4 model;

uniform bool dashed;
uniform vec2 dash_pattern;

flat out vec3 startPos;
out vec3 vertPos;

float rnd(float i) { return mod(4000. * sin(23464.345 * i + 45.345), 1.); }
void main() {
  vec4 mvp_vec = camMatrix * model * vec4(aPos, 1);
  vClipPos = mvp_vec;
  gl_Position = mvp_vec;
  gl_PointSize = 1;
  vertPos = vec4(aPos, 1).xyz / vec4(aPos, 1).w;
  startPos = vertPos;
  f_color = vec4(rnd(aPos.x), rnd(aPos.y), rnd(aPos.z), 1.0);
}
