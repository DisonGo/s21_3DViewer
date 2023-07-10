#version 330 core
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
  // vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
  // if (roundCircle && dot(circCoord, circCoord) > 1.0) {
  //   discard;
  // }
  // vec2 dir = (f_vertPos.xy - f_startPos.xy) * u_resolution / 2.0;
  // float dist = length(dir);

  // if (fract(dist / (u_dashSize + u_gapSize)) >
  //     u_dashSize / (u_dashSize + u_gapSize))
  //   discard;
  //    if (dashed) {
  //        float width = line_width * (1.0 - 2.0 * abs(mod(pattern_value,
  //        dash_pattern.x + dash_pattern.y) - dash_pattern.x) / (dash_pattern.x
  //        + dash_pattern.y));

  //       // Determine if this fragment is part of a dash or a gap
  //        bool is_dash = pattern_value < dash_pattern.x;
  //        if (is_dash) {
  //            FragColor = vec4(f_color.rgb, f_color.a * smoothstep(0.0, 1.0,
  //            width));
  //        } else {
  //            FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  //        }
  //    }
}
