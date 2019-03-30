#version 330

// Output color
layout(location = 0) out  vec4 color;
uniform flat alpha;

void main()
{
    vec3 black = vec3(1.0, 1.0, 1.0);
	color = vec4(black, alpha);
}
