#version 400 core
in vec2 texture_coordinates;

uniform sampler2D _texture;

void main()
{
	gl_FragColor = texture(_texture, texture_coordinates);
}
