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

vec2 distort(vec2 uv) {
	vec2 coord = uv.xy;
	float X = uv.x * 20.f;
    float Y = uv.y * 10.f;
    coord.y += cos(X+Y)*0.009;
    coord.x += sin(X-Y)*0.005;
    return coord;
}

void main()
{
    vec2 uv_delta = vec2(uv2.x - uv1.x, uv2.y - uv1.y);
    vec2 true_uv = vec2(
        uv1.x + texcoord.x * uv_delta.x,
        uv1.y + texcoord.y * uv_delta.y
    );
	vec2 coord = distort(texcoord);
    color = texture(sampler0, coord).ggra;
}