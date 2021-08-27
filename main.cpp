#include <stdio.h>
#include <chrono>

#include "src/utils/GLIncludes.h" // should be included first in the app to prevent gl.h dependency error
#include "src/application/Application.h"
#include "src/game/GameManager.h"
#include "src/game/GameLayer.h"
#include "src/game/UILayer.h"
#include "src/game/MenuLayer.h"
#include "src/application/InputManager.h"

class UnkPlanetWalkerApplication : public Application
{
public:
	UnkPlanetWalkerApplication(std::string name, int width, int height)
		: Application(name, width, height),
          game_layer(GameLayer(application_settings())),
          ui_layer(UILayer(application_settings())),
          menu_layer(MenuLayer(application_settings(), game_layer, ui_layer))
	{};

private:
    GameLayer game_layer;
    UILayer ui_layer;
    MenuLayer menu_layer;

protected:
	void OnInit()
	{
		AddLayer(&game_layer);
		AddLayer(&ui_layer);
        AddLayer(&menu_layer);
	}

    void ShowMenu()
    {
        game_layer.SetVisible(false);
        ui_layer.SetVisible(false);
        menu_layer.SetVisible(true);
    }

    void ShowGame()
    {
        game_layer.SetVisible(true);
        ui_layer.SetVisible(true);
        menu_layer.SetVisible(false);
    }

    void CheckIfGameIsOver()
    {
        PlayerStats *player_stats = GameManager::GetInstance().player_stats();

        if (player_stats->hp <= 0)
        {
            ShowMenu();
        }
    }

    void OnUpdate(long double dt)
    {
        if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_ESCAPE))
        {
            if (menu_layer.visible())
            {
                ShowGame();
            }
            else
            {
                ShowMenu();
            }
        }

        CheckIfGameIsOver();
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
