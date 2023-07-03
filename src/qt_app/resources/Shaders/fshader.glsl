#version 330 core
#define do_samples
in vec4 f_color;
//in float pattern_value;
float num_samples =0.0;
out vec4 FragColor;
uniform vec3 iResolution;
uniform bool roundCircle;
uniform vec2 dash_pattern;
uniform bool dashed;
uniform float line_width;
vec4 GetFragValAt( vec2 uv )
{
    num_samples += 1.0;

    // dot is same as uv.x*uv.x+uv.y+uv.y
    return vec4( dot( uv, uv) <= 0.4);
}

void mainImage(in vec2 fragCoord )
{

    // Normalized pixel coordinates (from -1 to 1)
    vec2 uv =  (2.*fragCoord - iResolution.xy) / iResolution.y;

    // Change offset to adjust sampling distance
    float offset = 1./iResolution.y;

    FragColor = GetFragValAt( uv );

    #ifdef do_samples
    // samples in +/- x direction
    FragColor += GetFragValAt(uv + vec2( offset, 0.0));
    FragColor += GetFragValAt(uv + vec2( -offset, 0.0));

    // samples in +/- y direction
    FragColor += GetFragValAt(uv + vec2( 0.0, offset ));
    FragColor += GetFragValAt(uv + vec2( 0.0, -offset));

    // samples at diagonals
    FragColor += GetFragValAt(uv + vec2(offset, offset));
    FragColor += GetFragValAt(uv + vec2(-offset, offset));
    FragColor += GetFragValAt(uv + vec2(offset, -offset));
    FragColor += GetFragValAt(uv + vec2(-offset, -offset));
    #endif

    FragColor /= num_samples;

}
void main() {

    vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
//    if (roundCircle && dot(circCoord, circCoord) > 1.0) {
//        discard;
//    }
    mainImage(gl_PointCoord);
    FragColor = mix(FragColor, f_color, 1);
//    if (dashed) {
//        float width = line_width * (1.0 - 2.0 * abs(mod(pattern_value, dash_pattern.x + dash_pattern.y) - dash_pattern.x) / (dash_pattern.x + dash_pattern.y));

//       // Determine if this fragment is part of a dash or a gap
//        bool is_dash = pattern_value < dash_pattern.x;
//        if (is_dash) {
//            FragColor = vec4(f_color.rgb, f_color.a * smoothstep(0.0, 1.0, width));
//        } else {
//            FragColor = vec4(0.0, 0.0, 0.0, 0.0);
//        }
//    }
}


