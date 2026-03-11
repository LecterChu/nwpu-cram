uniform sampler2D u_texture;
uniform vec2 u_resolution;
uniform vec2 u_pixel_size;

void main() {
    vec2 pos = gl_FragCoord.xy;
    vec2 pixelated_pos = (floor(pos / u_pixel_size) + 0.5) * u_pixel_size;
    gl_FragColor = texture2D(u_texture, pixelated_pos / u_resolution);
}