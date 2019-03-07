#version 330
// Input attributes
in vec3 in_position;

// Passed to fragment shader
out float pos_x;

// Application data
uniform mat3 transform;
uniform mat3 projection;

void main()
{
	vec3 pos = projection * transform * vec3(in_position.xy, 1.0);
	pos_x = in_position.x + 0.5;
//    vec3 pos = transform * vec3(in_position.xy, 1.0);
	gl_Position = vec4(pos.xy, in_position.z, 1.0);
}
