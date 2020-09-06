#version 430

in vec4 v_Color;
in vec2 v_Uv;
out vec4 FragmentColor;

uniform sampler2D u_Texture;

void main()
{
	FragmentColor = texture(u_Texture, v_Uv);
}