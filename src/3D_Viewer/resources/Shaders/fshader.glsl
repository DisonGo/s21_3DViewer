#version 410 core

flat in vec4 f_startPos;
in vec4 f_vertPos;

out vec4 FragColor;
uniform bool u_circlePoint;
uniform bool u_dashed;

uniform float u_dashSize;
uniform float u_gapSize;

uniform vec2 u_resolution;
uniform vec3 u_prototype_color;

void main() {
  // FragColor = mix(vec4(0, 0, 0, 1), f_color, 0.75);
  FragColor = vec4(u_prototype_color, 1);
  vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
  if (u_circlePoint && dot(circCoord, circCoord) > 1.0) {
    discard;
  }
  vec2 dir = (f_vertPos.xy - f_startPos.xy) * u_resolution / 2.0;
  float dist = length(dir);

  if (u_dashed) {
    if (fract(dist / (u_dashSize + u_gapSize)) >
        u_dashSize / (u_dashSize + u_gapSize))
      discard;
  }
}
