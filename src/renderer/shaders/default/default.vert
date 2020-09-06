#version 430

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec4 i_Color;

out vec4 v_Color;

void main()
{
	gl_Position = vec4(i_Position, 1.0);
	v_Color = i_Color;
}