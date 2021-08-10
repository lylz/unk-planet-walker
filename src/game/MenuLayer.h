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
    Button *button_;

 public:
    MenuLayer(ApplicationSettings *application_settings)
        : Layer(application_settings) {};

    ~MenuLayer()
    {
        delete button_;
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

        button_ = new Button("button", { 512, 360 });
    }

    void OnUpdate()
    {
        if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_ESCAPE))
        {
            SetVisible(!visible());
        }

        if (visible())
        {
            if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_C))
            {
                button_->ChangeColor({ 0.5, 0.5, 0.5, 1 });
            }
        }
    }

    void OnRender()
    {
        GLWCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLWCall(glClearColor(0.0, 0.0, 0.0, 1.0));

        button_->OnRender();
    }

};
