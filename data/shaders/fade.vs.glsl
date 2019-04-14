#version 330
// Input attributes
in vec3 in_position;

// Passed to fragment shader

// Application data
uniform mat3 transform;
uniform mat3 projection;

void main()
{
	vec3 pos = projection * transform * vec3(in_position.xy, 1.0);
	gl_Position = vec4(pos.xy, in_position.z, 1.0);
}