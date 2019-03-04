#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec3 v_coordinates;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 Color;

uniform vec3 Parametrii;

out vec3 frag_position;
out vec3 frag_normal;
out vec3 frag_coordinates;
out vec3 frag_color;

void main()
{
	frag_position = v_position;
	frag_normal = v_normal;
	frag_coordinates = v_coordinates;
	frag_color = Color;

	gl_Position = Projection * View * mat4( 
		 1,  0, 0,  0,     // coloana 1 in memorie 
		 0,  1, 0,  0,     // coloana 2 in memorie 
		 0,  0, 1,  0,     // coloana 3 in memorie 
		 Parametrii.x, Parametrii.y, Parametrii.z, 1) * Model * vec4(v_position, 1.0);
}
