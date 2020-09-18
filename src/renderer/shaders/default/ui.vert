#version 430

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec4 i_Color;
layout (location = 2) in vec2 i_Uv;
layout (location = 3) in float i_TextureId;

uniform mat4 u_Ortho;

out vec4 v_Color;
out vec2 v_Uv;
out float v_TextureId;

void main()
{
	v_Uv = i_Uv;
	v_Color = i_Color;
	v_TextureId = i_TextureId;
	gl_Position = u_Ortho * vec4(i_Position, 1.0);
}