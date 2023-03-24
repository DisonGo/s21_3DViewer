#version 400 core
uniform mat4 mvp_matrix;
in vec3 color;
in vec4 a_position;
out vec4 f_color;
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;
    gl_PointSize = 10.0;
    f_color = vec4(color, 1.0);
}
