#version 430

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec4 i_Color;
layout (location = 2) in vec2 i_Uv;
layout (location = 3) in float i_TextureId;

out vec4 v_Color;
out vec2 v_Uv;
out float v_TextureId;

void main()
{
	v_Uv = i_Uv;
	v_Color = i_Color;
	v_TextureId = i_TextureId;
	gl_Position = vec4(i_Position * 0.05, 1.0);
}