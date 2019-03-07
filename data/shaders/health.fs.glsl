#version 330
// From vertex shader
in float pos_x;

// Application data
uniform vec3 start_color;
uniform vec3 end_color;

// Output color
layout(location = 0) out  vec4 color;

bool between(float x, float start, float end){
    return start <= x && x <= end;
}

void main()
{
    int n = 5;
    float i = 1.0f / n;
    float segment_thickness = 0.03;
    float stroke_thickness = 0.07;
    vec3 s = vec3(231.0, 76.0, 60.0) / 256.0;
    vec3 c = vec3(46.0, 204.0, 113.0) / 256.0;
    vec3 fcolor = mix(start_color, end_color, pos_x);
//    if (mod(pos_x, i) <= segment_thickness) { // thickness of segments
//        color = vec4(0.0); // Blank
//    } else {
//	}
        color = vec4(fcolor, 1.0);
}
