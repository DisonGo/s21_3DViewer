#version 330 core
in vec4 f_color;
in float pattern_value;

out vec4 FragColor;
uniform bool roundCircle;
uniform vec2 dash_pattern;
uniform bool dashed;
uniform float line_width;
void main() {
    FragColor = f_color;
    vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
    if (dot(circCoord, circCoord) > 1.0 && roundCircle) {
        discard;
    }
    if (dashed) {
        float width = line_width * (1.0 - 2.0 * abs(mod(pattern_value, dash_pattern.x + dash_pattern.y) - dash_pattern.x) / (dash_pattern.x + dash_pattern.y));

       // Determine if this fragment is part of a dash or a gap
        bool is_dash = pattern_value < dash_pattern.x;
        if (is_dash) {
            FragColor = vec4(f_color.rgb, f_color.a * smoothstep(0.0, 1.0, width));
        } else {
            FragColor = vec4(0.0, 0.0, 0.0, 0.0);
        }
    }
}
