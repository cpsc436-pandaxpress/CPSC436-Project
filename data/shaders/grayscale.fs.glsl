#version 330
// From vertex shader
in vec2 texcoord;

// Application data
uniform sampler2D sampler0;
uniform vec3 fcolor;
uniform vec2 uv1;
uniform vec2 uv2;

// Output color
layout(location = 0) out  vec4 color;

void main()
{
    vec2 uv_delta = vec2(uv2.x - uv1.x, uv2.y - uv1.y);
    vec2 true_uv = vec2(
        uv1.x + texcoord.x * uv_delta.x,
        uv1.y + texcoord.y * uv_delta.y
    );
    vec4 og_color = texture(sampler0, vec2(true_uv.x, true_uv.y));
    float average = 0.2126 * og_color.r + 0.7152 * og_color.g + 0.0722 * og_color.b;
    color = vec4(average, average, average, og_color.a);
}
