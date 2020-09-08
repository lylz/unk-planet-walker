#include <stdio.h>
#include <chrono>

#include "src/utils/GLIncludes.h" // wierd hackish stuff should be included first in the app to prevent an dependency error about gl.h
#include "src/application/Application.h"
#include "SceneLayer.h"
#include "UILayer.h"

class UnkPlanetWalkerApplication : public Application
{
public:
	UnkPlanetWalkerApplication(std::string name, int width, int height)
		: Application(name, width, height)
	{};

protected:
	void OnInit()
	{
		// TODO: rendering is bugged now. fix it
		AddLayer(new UILayer);
		AddLayer(new SceneLayer);
	}
};

int main()
{
	try
	{
		UnkPlanetWalkerApplication app("Unk Planet Walker", 1024, 720);

		app.Run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
