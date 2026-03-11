#version 120

uniform sampler2D u_texture;
uniform float u_brightness_threshold;

void main() {
    vec2 texCoord = gl_TexCoord[0].xy;
    vec4 color = texture2D(u_texture, texCoord);
    vec3 brightness = vec3(0.2126, 0.7152, 0.0722);

    if (dot(color.rgb, brightness) > u_brightness_threshold) {
        gl_FragColor = color;
    } else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}