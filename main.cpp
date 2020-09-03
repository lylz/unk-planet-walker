#include <stdio.h>

#include "src/utils/GLIncludes.h" // wierd hackish stuff should be included first in the app to prevent an dependency error about gl.h
#include "src/Window.h"
#include "src/InputManager.h"
#include "src/renderer/Renderable2D.h"
#include "src/renderer/Renderer.h"

int main()
{
	Window window("Unk Planet Walker", 512, 512);

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		printf("ERROR: unable initialize glew. \n");
		exit(EXIT_FAILURE);
	}

	Renderable2D cube;
	Renderer renderer;

	while (!window.ShouldClose())
	{
		renderer.Prepare();
		renderer.Render({ &cube });

		window.Update();

		if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_ENTER))
		{
			printf("Enter was pressed, yey!\n");
		}
	}

	return 0;
}
