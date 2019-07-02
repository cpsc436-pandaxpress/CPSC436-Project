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
    vec4 og_color = vec4(fcolor, 1.0) * texture(sampler0, vec2(true_uv.x, true_uv.y));
    float outputRed = (og_color.r * .393) + (og_color.g *.769) + (og_color.b * .189);
    float outputGreen = (og_color.r * .349) + (og_color.g *.686) + (og_color.b * .168);
    float outputBlue = (og_color.r * .272) + (og_color.g *.534) + (og_color.b * .131);
    color = vec4(outputRed, outputGreen, outputBlue, og_color.a);
}
