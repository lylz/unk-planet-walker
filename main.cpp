#include <stdio.h>

#include "src/utils/GLIncludes.h" // wierd hackish stuff should be included first in the app to prevent an dependency error about gl.h
#include "src/Window.h"
#include "src/InputManager.h"
#include "src/renderer/Renderable2D.h"
#include "src/renderer/Renderer.h"
#include "src/renderer/materials/default/ColorMaterial.h"

#include "src/utils/Randomizer.h"

int main()
{
	Window window("Unk Planet Walker", 512, 512);

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		printf("ERROR: unable initialize glew. \n");
		exit(EXIT_FAILURE);
	}

	Shader *color = Shader::CreateFromFiles("src/renderer/shaders/default/color.vert", "src/renderer/shaders/default/color.frag");
	ColorMaterial *color_material = new ColorMaterial(color);
	Renderable2D cube(color_material);
	Renderer renderer;

	while (!window.ShouldClose())
	{
		renderer.Prepare();
		renderer.Render({ &cube });

		window.Update();

		if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_ENTER))
		{
			double r = Randomizer::GetInstance().Random(0.0, 1.0);
			double g = Randomizer::GetInstance().Random(0.0, 1.0);
			double b = Randomizer::GetInstance().Random(0.0, 1.0);

			color_material->SetColor(glm::vec3(r, g, b));
		}
	}

	return 0;
}
