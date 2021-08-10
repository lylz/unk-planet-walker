#version 430

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec4 i_Color;

uniform mat4 u_Ortho;
uniform vec4 u_Color;

out vec4 v_Color;
out vec2 v_Uv;

void main()
{
	v_Color = u_Color;
	gl_Position = u_Ortho * vec4(i_Position, 1.0);
}