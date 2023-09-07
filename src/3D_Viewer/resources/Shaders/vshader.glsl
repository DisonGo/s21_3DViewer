#version 410 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
flat out vec4 f_startPos;
out vec4 f_vertPos;
out vec3 f_normal;
flat out vec3 f_normal_flat;
uniform mat4 u_camMatrix;
uniform mat4 u_modelMatrix;
uniform mat4 u_modelMatrixInvTrans;
uniform mat4 u_CameraView;
uniform mat4 u_CameraProjection;

uniform vec2 u_dash_pattern;

uniform float u_pointSize;

float rnd(float i) { return mod(4000. * sin(23464.345 * i + 45.345), 1.); }
void main() {
  vec4 mvp_vec =
      u_CameraProjection * u_CameraView * u_modelMatrix * vec4(aPos, 1);
  gl_Position = mvp_vec;
  gl_PointSize = u_pointSize;
  f_startPos = f_vertPos = mvp_vec;
  f_normal_flat = f_normal =
      normalize((u_modelMatrixInvTrans * vec4(aNormal, 1)).xyz);
}
