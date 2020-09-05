#version 430

layout (location = 0) in vec3 vPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * vec4(vPosition, 1.0);
}