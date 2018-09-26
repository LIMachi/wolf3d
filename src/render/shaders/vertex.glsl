#version 400 core
layout (location = 0) in vec3 _position;
layout (location = 1) in vec2 _texture_coordinates;

out vec texture_coordinates;

void main()
{
	gl_Position = vec4(_position, 1.0);
	texture_coordinates = _texture_coordinates;
}
