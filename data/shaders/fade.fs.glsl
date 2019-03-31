#version 330

// Output color
layout(location = 0) out  vec4 color;
uniform float alpha;

void main()
{
    vec3 black = vec3(0.f, 0.f, 0.f);
	color = vec4(black, alpha);
}
