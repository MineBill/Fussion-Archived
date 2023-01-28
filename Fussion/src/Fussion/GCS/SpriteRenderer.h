#pragma once
#include "Fussion/GCS/Component.h"
#include "Fussion/GCS/GameObject.h"
#include "Fussion/Rendering/2D/Renderer2D.h"
#include "Fussion/Rendering/Texture.h"

namespace Fussion
{
    class SpriteRenderer : public Component
    {
        Ref<Texture> m_sprite{};
        glm::vec2 m_texture_coordinates{1, 1};

    public:
        void on_update(f32) override;
        void on_editor_gui() override;

        void set_texture(const Ref<Texture> &new_texture);

        StringView name() override
        {
            return "SpriteRenderer";
        }
    };
} // namespace Fussion
