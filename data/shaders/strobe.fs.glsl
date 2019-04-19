#version 330
// From vertex shader
in vec2 texcoord;

// Application data
uniform sampler2D sampler0;
uniform vec3 fcolor;
uniform vec2 uv1;
uniform vec2 uv2;
uniform float timeElapsed;

// Output color
layout(location = 0) out  vec4 color;

void main()
{
    vec2 uv_delta = vec2(uv2.x - uv1.x, uv2.y - uv1.y);
    vec2 true_uv = vec2(
        uv1.x + texcoord.x * uv_delta.x,
        uv1.y + texcoord.y * uv_delta.y
    );
    vec3 colors[9] = vec3[](
        vec3(0.9, 0.1, 1.0),  //magenta
        vec3(1.0, 1.0, 0.0), //yellow
        vec3(1.0, 0.5, .0), //orange
        vec3(0.2, 1.0, 1.0), //cyan
        vec3(1.0, 0.9, 0.0), //more yellow
        vec3(1.0, 0.0, 0.0), //red
        vec3(0.4, 1.0, 0.4), //green
        vec3(0.0, 0.4, 0.8), //indigo
        vec3(0.5, 0.0, 1.0) //violet
    );
    int t = int(timeElapsed*10);
    int index = int(mod(t, 9));
    vec3 colorHighlight = colors[index];
    color = vec4(colorHighlight, 1.0) * texture(sampler0, vec2(true_uv.x, true_uv.y));
}
