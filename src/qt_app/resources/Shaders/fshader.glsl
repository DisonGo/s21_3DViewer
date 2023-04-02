#version 330 core
in vec4 f_color;
//vec3 color = vec3(1.0, 0.0, 0.0);
out vec4 FragColor;
uniform bool roundCircle;
void main() {
    FragColor = f_color;
    vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
    if (dot(circCoord, circCoord) > 1.0 && roundCircle) {
        discard;
    }
}
