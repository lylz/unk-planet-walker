#version 430

in vec4 v_Color;
in vec2 v_Uv;
in float v_TextureId;

out vec4 FragmentColor;

uniform sampler2D u_Texture[32];

void main()
{
	// TODO: add v_TextureId null check
	int textureId = int(v_TextureId - 0.5);
	FragmentColor = texture(u_Texture[textureId], v_Uv);
}