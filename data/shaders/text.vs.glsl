#version 330 core
in vec2 in_position;
in vec2 in_texcoord;
out vec2 TexCoords;

uniform mat3 projection;

void main()
{
    TexCoords = in_texcoord;
    vec3 pos = projection * vec3(in_position, 1.0);
    gl_Position = vec4(pos.xy, 0.0, 1.0);
}