#include <stdio.h>
#include <chrono>

#include "src/utils/GLIncludes.h" // should be included first in the app to prevent gl.h dependency error
#include "src/application/Application.h"
#include "MapLayer.h"
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
		AddLayer(new MapLayer);
		AddLayer(new SceneLayer);
		AddLayer(new UILayer);
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
