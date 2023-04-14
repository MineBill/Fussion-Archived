#include "ViewportPanel.h"
#include "Fussion/Rendering/2D/Renderer2D.h"
#include <Fussion/Scene/Components.h>
#include <Fussion/Scene/Entity.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <ImGuiFileDialog.h>
#include <ImGuiHelpers.h>
#include <filesystem>
#include <imgui_internal.h>

Editor::ViewportPanel::ViewportPanel()
{
    // @Note Will crash if RendererAPI is not initialized yet
    m_frame_buffer = Framebuffer::WithSize(100, 100);
}

void Editor::ViewportPanel::on_draw(Optional<Entity> selected, Entity camera_entity, Scene &scene, f32 delta)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
    ImGui::Begin("Viewport");
    {
        auto start = ImGui::GetCurrentWindow()->DC.CursorPos;
        m_is_focused = ImGui::IsWindowHovered();
        const auto id = m_frame_buffer->color_attachment();
        auto min = ImGui::GetWindowContentRegionMin();
        auto max = ImGui::GetWindowContentRegionMax();

        auto pos = ImGui::GetWindowPos();
        min.x += pos.x;
        min.y += pos.y;
        max.x += pos.x;
        max.y += pos.y;
        m_position = {pos.x, pos.y};

        const auto new_viewport_size = glm::vec2{max.x - min.x, max.y - min.y};
        if (new_viewport_size != m_size) {
            m_frame_buffer->resize(static_cast<u32>(new_viewport_size.x), static_cast<u32>(new_viewport_size.y));
            scene.on_resized(static_cast<i32>(new_viewport_size.x), static_cast<i32>(new_viewport_size.y));
        }
        m_size = new_viewport_size;

        ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<u64>(id)), {max.x - min.x, max.y - min.y}, // NOLINT
                     {0, 0},                                                                              // NOLINT
                     {1, -1});

        ImGui::GetCurrentWindow()->DC.CursorPos = start + ImVec2(10, 10);

        const auto stats = Renderer2D::draw_stats();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));

        ImGuiHelpers::BeginGroupPanel("Renderer");
        ImGui::Text("Draw-calls: %d", stats.draw_calls);
        ImGui::Text("Vertices: %d", stats.vertices());
        ImGuiHelpers::EndGroupPanel();

        ImGui::GetCurrentWindow()->DC.CursorPos += ImVec2(10, 10);
        ImGuiHelpers::BeginGroupPanel("Other");
        ImGui::Text("Frame Time: %.2fms", static_cast<f64>(delta * 1000));
        ImGui::Text("FPS: %d", static_cast<i32>(1.0f / delta));
        ImGuiHelpers::EndGroupPanel();

        // Gizmos
        if (auto entity = selected) {
            (void)selected;
            auto draw_list = ImGui::GetCurrentWindow()->DrawList;
            // Get the selected entity position
            // Get the editor camera
            // Convert the entity position to screen space
            // Draw the gizmo
            auto camera = camera_entity.get_component<CameraComponent>().camera;

            auto screen_position = camera.world_to_screen(entity->transform().position);
            auto camera_position = camera.world_to_screen(camera_entity.transform().position);
            auto start_position = m_position - glm::vec2(screen_position) + camera_position;

            ImGuiHelpers::RenderSimpleRect(draw_list, start_position, {20, 20}, 0xff0000ff, 2.0f);
        }

        ImGui::PopStyleColor();
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

bool Editor::ViewportPanel::on_event(Event &e)
{
    (void)e;
    return false;
}
