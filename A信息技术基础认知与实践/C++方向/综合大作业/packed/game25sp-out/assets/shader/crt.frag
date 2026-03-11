#version 120

uniform sampler2D u_texture;
uniform float u_time;

uniform float u_chromatic_strength;

void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    vec2 center = vec2(0.5, 0.5);

    // barrel distortion on the edges
    float k = 0.1;
    vec2 coord_distorted = uv - center;
    float r = length(coord_distorted);
    float f = 1.0 + k * r * r;
    uv = coord_distorted * f + center;

    // color distortion
    vec2 offset = uv - center;
    float chromatic_strength = u_chromatic_strength;
    vec4 color;

    color.r = texture2D(u_texture, uv + offset * chromatic_strength).r;
    color.g = texture2D(u_texture, uv).g;
    color.b = texture2D(u_texture, uv - offset * chromatic_strength).b;
    color.a = texture2D(u_texture, uv).a;

    gl_FragColor = color;

    // cropping
    float cropping_start = 0.98;
    float cropping_end = 1.0;
    float distance_from_center = max(abs(uv.x - 0.5) * 2.0, abs(uv.y - 0.5) * 2.0);
    float smoothed = 1.0 - smoothstep(cropping_start, cropping_end, distance_from_center);
    gl_FragColor *= smoothed;

    // brightness falloff
    float edge_falloff_strength = 2;
    float dist_from_center = length(uv - center);
    float brightness_multiplier = 1.0 - pow(dist_from_center, edge_falloff_strength);
    gl_FragColor.rgb *= brightness_multiplier;

    // scan lines
    float scanline_strength = 0.05;
    float scanline_freq = 5.0; // for every n lines,
    float scanline_width = 2.0; // make m of them dimmer
    float scanline_speed = 0.02;
    float scanline_offset = u_time * scanline_speed;
    if (mod(gl_FragCoord.y + scanline_offset, scanline_freq) < scanline_width)
    {
        gl_FragColor *= (1.0 - scanline_strength);
    }

}