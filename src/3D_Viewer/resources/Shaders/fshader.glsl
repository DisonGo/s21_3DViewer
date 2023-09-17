#version 410 core

struct Light {
  vec3 position;
  vec3 color;
  float strength;
};
struct PointLight {
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

flat in vec4 f_startPos;
in vec3 f_vertPos;
flat in vec3 f_vertPos_flat;
in vec3 f_normal;
flat in vec3 f_normal_flat;
out vec4 FragColor;
uniform bool u_circlePoint;
uniform bool u_dashed;
uniform bool u_flat_shade;
uniform bool u_do_lighting;
uniform vec3 u_lightPos;

uniform Light[10] u_ligths;
uniform float u_dashSize;
uniform float u_gapSize;

uniform vec2 u_resolution;
uniform vec3 u_prototype_color;

uniform vec3 u_CameraPos;
float specular_shininess = 8;
vec4 p_color = vec4(u_prototype_color, 1);

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
vec4 CalcAmbient(vec3 color, float strength) {
  return vec4(color, 1) * strength;
}
float CalcDiffuse(vec3 normal, vec3 light_direction) {
  return max(dot(normal, light_direction), 0.0);
}
float CalcSpecular(vec3 reflection_direction, vec3 view_direction,
                   float shininess) {
  return pow(CalcDiffuse(view_direction, reflection_direction), shininess);
}
vec3 CalcDirLight(vec3 position, vec3 color, float strength) {
  if (strength == 0) return vec3(0);
  vec3 norm;
  if (u_flat_shade)
    norm = normalize(f_normal_flat);
  else
    norm = normalize(f_normal);
  vec3 light_dir = normalize(norm - position);
  float diff = max(dot(norm, light_dir), 0.0);

  float diffuse = CalcDiffuse(norm, light_dir);

  vec3 viewDir = normalize(u_CameraPos - f_vertPos.xyz);
  vec3 reflectDir = reflect(-light_dir, norm);

  float specular =
      CalcSpecular(viewDir, reflectDir, specular_shininess) * strength;

  return (diffuse + specular) * color;
}
vec3 CalcPointLight(PointLight light, vec3 fragPos, vec3 viewDir,
                    float strength) {
  float constant = 1;
  float linear = 1;
  float quadratic = 1;
  vec3 norm;
  norm = normalize(u_flat_shade ? f_normal_flat : f_normal);
  vec3 lightDir = normalize(light.position - fragPos);
  // diffuse shading
  float diff = CalcDiffuse(norm, lightDir);
  // specular shading
  float angle = acos(dot(norm, lightDir));
  if (degrees(abs(angle)) >= 105) return vec3(0);
  float spec =
      CalcSpecular(viewDir, reflect(-lightDir, norm), specular_shininess);
  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
  // combine results
  vec3 ambient = light.ambient;
  vec3 diffuse = light.diffuse * diff;
  vec3 specular = light.specular * spec;

  return (ambient + diffuse + specular) * attenuation * strength;
}

vec4 SoftLightBlend(vec4 color1, vec4 color2) {
  vec4 one = vec4(1.0);
  vec4 double_mix = 2.0 * color1 * color2;
  vec4 inverse2 = one - color2;
  vec4 c1 = (2.0 * color1 - one) * inverse2 + double_mix;
  vec4 c2 = (sqrt(color1) * inverse2) + double_mix;
  return mix(c1, c2, step(0.1, color1));
}
void main() {
  if (u_do_lighting) {
    vec3 final_light = vec3(0);
    vec4 total_ambient = vec4(0);
    vec3 vPos = u_flat_shade ? f_vertPos_flat : f_vertPos;
    vec3 viewDir = normalize(u_CameraPos - vPos);
    int lights_count = 1;
    for (int i = 0; i < lights_count; i++) {
      PointLight p_light = PointLight(
          u_ligths[i].position, 1, 0.045, 0.0075, u_ligths[i].color * 0.2,
          u_ligths[i].color, u_ligths[i].color * 1.1);

      final_light +=
          CalcPointLight(p_light, vPos, viewDir, u_ligths[i].strength);
    }
    FragColor = vec4(final_light, 1) * p_color;
  } else {
    FragColor = p_color;
  }
  DecideLineDraw();
  DecidePointDraw();
}
