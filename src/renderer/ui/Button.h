#pragma once

#include "Text.h"
#include "../BatchRenderer.h"
#include "../Renderer.h"
#include "../materials/default/UIMaterial.h"
#include "../materials/default/UIButtonMaterial.h"
#include "../Mesh.h"

class Button
{
 public:
    Button(const std::string &text, glm::vec2 screen_position);
    ~Button();

    void OnRender();
    void ChangeColor(glm::vec4 color);

 private:
    BatchRenderer *batch_renderer_;
    Renderer *renderer_;

    glm::vec2 screen_position_;
    Text *text_;
    Mesh *button_mesh_;

    UIMaterial *ui_material_;
    UIButtonMaterial *ui_button_material_;
};

