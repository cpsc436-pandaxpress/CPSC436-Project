#version 330

// From Vertex Shader
in vec3 vcolor;
in vec2 vpos; // Distance from local origin

// Output color
layout(location = 0) out  vec4 color;

void main()
{
    vec3 brown = vec3(1.0, 1.0, 1.0);
	color = vec4(0.5, 0.5, 0.5, 1.0); //just white

}