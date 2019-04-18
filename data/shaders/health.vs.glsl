#version 330
// Input attributes
in highp vec3 in_position;

// Passed to fragment shader
out float pos_x;
out float pos_y;

// Application data
uniform mat3 transform;
uniform mat3 projection;

void main()
{
	pos_x = in_position.x + 0.5;
	pos_y = in_position.y + 0.5;
	float slant_factor = 15.0;
	mat3 slanted = mat3(
            vec3(1.0, 0.0, 0.0),
            vec3(0.0, 1.0, 0.0),
            vec3(- pos_y / slant_factor, 0.0, 1.0)
    );
	vec3 pos = projection * transform * slanted * vec3(in_position.xy, 1.0);
//    vec3 pos = transform * vec3(in_position.xy, 1.0);
	gl_Position = vec4(pos.xy, in_position.z, 1.0);
}
