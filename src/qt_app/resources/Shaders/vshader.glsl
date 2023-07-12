#version 410 core
layout(location = 0) in vec3 aPos;
flat out vec4 f_startPos;
out vec4 f_vertPos;

uniform mat4 u_camMatrix;
uniform mat4 u_modelMatrix;

uniform vec2 u_dash_pattern;

uniform float u_pointSize;

float rnd(float i) { return mod(4000. * sin(23464.345 * i + 45.345), 1.); }
void main() {
  vec4 mvp_vec = u_camMatrix * u_modelMatrix * vec4(aPos, 1);
  gl_Position = mvp_vec;
  gl_PointSize = u_pointSize;
  f_startPos = f_vertPos = mvp_vec;
}
