#version 430

in vec4 v_Color;
in vec2 v_Uv;
in float v_TextureId;

out vec4 FragmentColor;

layout (binding = 0) uniform sampler2D u_Texture[32];

void main()
{
	vec4 color = vec4(0.5, 0.6, 0.7, 1.0);

	if (v_TextureId >= 0)
	{
		int textureId = int(v_TextureId);
		color = texture(u_Texture[textureId], v_Uv);
	}

	FragmentColor = color;
}