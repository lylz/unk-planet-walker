#version 430

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec4 i_Color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec4 v_Color;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * vec4(i_Position, 1.0);
	v_Color = i_Color;
}