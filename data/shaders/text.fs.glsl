#version 330 core
in vec2 texcoord;
out vec4 color;

uniform sampler2D text;
uniform vec3 fcolor;
uniform float opacity;

void main()
{
    vec3 outline_col = vec3(0.0, 0.0, 0.0); // e.g red

    vec2 tex = texture(text, texcoord).rg;
    float fill    = tex.r;
    float outline = tex.g;

    float alpha    = opacity * max( fill, outline );
    vec3 mix_color = mix( mix(vec3(0.0), fcolor, fill), outline_col, outline );

    color = vec4(mix_color, alpha);
}