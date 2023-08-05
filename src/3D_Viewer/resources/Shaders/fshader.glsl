#version 410 core

flat in vec4 f_startPos;
in vec4 f_vertPos;
in vec3 f_normal;
out vec4 FragColor;
uniform bool u_circlePoint;
uniform bool u_dashed;
uniform bool u_do_lighting;
uniform vec3 u_lightPos;

uniform float u_dashSize;
uniform float u_gapSize;

uniform vec2 u_resolution;
uniform vec3 u_prototype_color;

uniform vec3 u_CameraPos;

vec3 lightColor = vec3(1., 1., 1.);
float ambientStrength = 0.1;
float specularStrength = 0.2;

void DecidePointDraw() {
  vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
  if (u_circlePoint && dot(circCoord, circCoord) > 1.0) {
    discard;
  }
}
void DecideLineDraw() {
  vec2 dir = (f_vertPos.xy - f_startPos.xy) * u_resolution / 2.0;
  float dist = length(dir);

  if (u_dashed) {
    if (fract(dist / (u_dashSize + u_gapSize)) >
        u_dashSize / (u_dashSize + u_gapSize))
      discard;
  }
}
vec3 DoLigthing() {
  vec3 ambient = ambientStrength * lightColor;

  vec3 norm = normalize(f_normal);
  vec3 lightDir = normalize(u_lightPos - f_vertPos.xyz);
  float diff = max(dot(norm, lightDir), 0.0);

  vec3 diffuse = diff * lightColor;

  vec3 viewDir = normalize(u_CameraPos - f_vertPos.xyz);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * lightColor;

  return ambient + diffuse + specular;
}
void main() {
  if (u_do_lighting)
    FragColor = vec4(DoLigthing() * u_prototype_color, 1);
  else
    FragColor = vec4(u_prototype_color, 1);
  DecidePointDraw();
  DecideLineDraw();
}
