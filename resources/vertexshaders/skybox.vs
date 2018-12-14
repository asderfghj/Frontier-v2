#version 330 core
layout (location = 0) in vec3 in_position;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 scaler;

void main()
{
	TexCoords = in_position;
	gl_Position = projection * view * scaler * vec4(in_position, 1.0);
}