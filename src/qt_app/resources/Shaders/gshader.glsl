#version 330 core
layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;
uniform mat4 m_CameraView;
uniform mat4 m_CameraProjection;
uniform vec3 u_CameraPos;
uniform mat4 model;
vec3 CameraRight_worldspace =
    vec3(m_CameraView[0][0], m_CameraView[1][0], m_CameraView[2][0]);
vec3 CameraUp_worldspace =
    vec3(m_CameraView[0][1], m_CameraView[1][1], m_CameraView[2][1]);
// out f_vertPos
uniform float u_lineWidth;
// vec3 v_line_vec = gl_in[1].gl_Position - gl_in[0].gl_Position;
// vec3 v_center = v_line_vec / vec3(2.);
void main() {
  mat4 m_mv = m_CameraProjection * m_CameraView * model;
  vec4 lineBegin = gl_in[0].gl_Position;
  vec4 lineEnd = gl_in[1].gl_Position;
  float th = u_lineWidth / 20;

  vec4 quadTL = lineBegin + vec4(0.0, 0.0, -th, 0.0);
  vec4 quadTR = lineEnd + vec4(0.0, 0.0, -th, 0.0);
  vec4 quadBL = lineBegin + vec4(0.0, 0.0, th, 0.0);
  vec4 quadBR = lineEnd + vec4(0.0, 0.0, th, 0.0);

  gl_Position = m_mv * quadTL;
  EmitVertex();
  gl_Position = m_mv * quadTR;
  EmitVertex();
  gl_Position = m_mv * quadBL;
  EmitVertex();
  gl_Position = m_mv * quadBR;
  EmitVertex();
  EndPrimitive();
}