#pragma once
#include "Panels/PropertiesEditorPanel.h"
#include "Panels/SceneTreePanel.h"
#include "Panels/ViewportPanel.h"
#include <Components/EditorCameraComponent.h>
#include <Fussion/Fussion.h>

namespace Editor
{
    class EditorLayer final : public Fussion::Layer
    {
        static EditorLayer *s_instance;

        Fussion::Ref<Fussion::Texture> m_texture, m_second_texture;

        bool m_show_renderer{false};
        bool m_show_demo_window{false};

        CameraComponent *m_scene_camera{nullptr};
        Entity m_scene_camera_entity{};
        SceneTreePanel m_scene_tree_panel{};
        ViewportPanel m_viewport_panel;
        PropertiesEditorPanel m_properties_editor_panel{};

        void main_interface(f32);
        void main_menubar();
        void renderer_statistics();

        Fussion::Scene m_scene{};

    public:
        EditorLayer() = default;
        ~EditorLayer() override = default;
        void on_load() override;
        void on_update(f32 delta) override;
        auto on_event(Fussion::Event &event) -> bool override;

        static EditorLayer &get();

        mustuse bool is_viewport_focused() const { return m_viewport_panel.is_focused(); }
    };
} // namespace Editor
