#include "Button.h"

#include "../font/FontManager.h"
#include "../shaders/ShaderManager.h"
#include "../MeshFactory.h"

Button::Button(const std::string &text, glm::vec2 screen_position)
{
    Font font = FontManager::GetInstance().Get("PixelFont");

    text_ = new Text(text, font, { screen_position });
    Shader *ui_shader = ShaderManager::GetInstance().Get("UI");

    assert(ui_shader != nullptr);

    ui_material_ = new UIMaterial(ui_shader);
    batch_renderer_ = new BatchRenderer(ui_material_);
    renderer_ = new Renderer();

    for (auto mesh: text_->meshes())
    {
        batch_renderer_->Submit(mesh);
    }

    glm::vec3 button_position = { screen_position.x, screen_position.y, 0 };
    glm::vec4 button_color = { 255, 255, 255, 1 };

    Shader *ui_button_shader = ShaderManager::GetInstance().Get("UIButton");

    assert(ui_button_shader != nullptr);

    ui_button_material_ = new UIButtonMaterial(ui_button_shader);
    ui_button_material_->ChangeColor({ 0.8, 0.8, 0.8, 1 });

    button_mesh_ = MeshFactory::CreateRectangle(100, 40, button_position, button_color, ui_button_material_);

    renderer_->Submit(button_mesh_);
}

void Button::ChangeColor(glm::vec4 color)
{
    ui_button_material_->ChangeColor(color);
}

void Button::OnRender()
{
    renderer_->Prepare();
    renderer_->Render();
    batch_renderer_->Render();
}

Button::~Button()
{
    delete batch_renderer_;
    delete renderer_;
    delete ui_material_;
    delete ui_button_material_;
    delete button_mesh_;
    delete text_;
}

