#pragma once

#include "../application/InputManager.h"
#include "../application/Layer.h"
#include "../renderer/materials/default/UIMaterial.h"
#include "../renderer/shaders/ShaderManager.h"
#include "../renderer/Camera.h"
#include "../renderer/font/FontLoader.h"
#include "../renderer/font/FontManager.h"
#include "../renderer/ui/Button.h"
#include "../utils/GLIncludes.h"

class MenuLayer : public Layer
{
 private:
    std::vector<Button *> buttons_;
    unsigned int cursor_position_ = 0;

 public:
    MenuLayer(ApplicationSettings *application_settings)
        : Layer(application_settings) {};

    ~MenuLayer()
    {
        for (auto button: buttons_)
        {
            delete button;
        }

        buttons_.clear();
    }

    void Init()
    {
        SetVisible(false);
        Font font = FontManager::GetInstance().Get("PixelFont");

        if (font.name == "")
        {
            font = FontLoader::Load("PixelFont", "assets/fonts/m6x11.ttf");
            FontManager::GetInstance().Add(font);
        }

        Shader *shader = ShaderManager::GetInstance().Get("UI");

        if (shader == nullptr)
        {
            shader = Shader::CreateFromFiles("UI", "src/renderer/shaders/default/ui.vert", "src/renderer/shaders/default/ui.frag");
            ShaderManager::GetInstance().Add(shader);
        }

        Shader *ui_button_shader = Shader::CreateFromFiles("UIButton", "src/renderer/shaders/default/ui_button.vert", "src/renderer/shaders/default/ui_button.frag");
        ShaderManager::GetInstance().Add(ui_button_shader);

        Button *restart_button = new Button("RESTART LEVEL", { 512, 360 });
        buttons_.push_back(restart_button);
        // TODO: change the way the positioning is calculated
        buttons_.push_back(new Button("QUIT", { 512, 360 - restart_button->height() - 20 }));
    }

    void OnUpdate()
    {
        if (visible())
        {
            if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_W))
            {
                if ((int) cursor_position_ - 1 < 0)
                {
                    cursor_position_ = 0;
                }
                else
                {
                    cursor_position_ -= 1;
                }
            }
            else if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_S))
            {
                if (cursor_position_ + 1 > buttons_.size() - 1)
                {
                    cursor_position_ = buttons_.size() - 1;
                }
                else
                {
                    cursor_position_ += 1;
                }
            }

            for (unsigned int i = 0; i < buttons_.size(); i++)
            {
                glm::vec4 color = { 0.3, 0.3, 0.3, 1 };

                if (i == cursor_position_)
                {
                    color = { 0.5, 0.5, 0.5, 1 };
                }

                buttons_[i]->ChangeColor(color);
            }
        }
    }

    void OnRender()
    {
        GLWCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLWCall(glClearColor(0.0, 0.0, 0.0, 1.0));

        for (auto button : buttons_)
        {
            button->OnRender();
        }
    }

};
