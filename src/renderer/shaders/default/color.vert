#version 430

layout (location = 0) in vec3 vPosition;
uniform vec4 inColor;
out vec4 color;

void main()
{
	gl_Position = vec4(vPosition, 1.0);
	color = inColor;
}