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
const float PI = 3.1415926535897932384626433832795;
void main() {
    vec2 uv_delta = vec2(uv2.x - uv1.x, uv2.y - uv1.y);
    vec2 true_uv = vec2(
        uv1.x + texcoord.x * uv_delta.x,
        uv1.y + texcoord.y * uv_delta.y
    );

    vec2 delta = 2.5*sin(PI * vec2(timeElapsed, 0.0));
    vec2 resolution = vec2(16.0, 9.0);

	vec2 dir = true_uv - vec2( .5 );
	float d = .7 * length( dir );
	dir = normalize( dir );
	vec2 value = d * dir * delta;

	vec4 c1 = texture(sampler0, true_uv - value / resolution.x );
	vec4 c2 = texture(sampler0, true_uv );
	vec4 c3 = texture(sampler0, true_uv + value / resolution.y );
	
	color = vec4( c1.r, c2.g, c3.b, c1.a + c2.a + c3.b );

}