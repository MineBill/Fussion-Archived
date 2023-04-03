#include "ViewportPanel.h"
#include "Fussion/Core/Application.h"
#include "Fussion/Rendering/2D/Renderer2D.h"
#include <Fussion/Scene/Components.h>
#include <Fussion/Scene/Entity.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <ImGuiFileDialog.h>
#include <ImGuiHelpers.h>
#include <filesystem>
#include <imgui_internal.h>

Editor::ViewportPanel::ViewportPanel()
{
    // @Note Will crash if RendererAPI is not initialized yet
    m_frame_buffer = Fussion::Framebuffer::WithSize(100, 100);
}

void Editor::ViewportPanel::on_draw(Fussion::Scene &scene, f32 delta)
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

        const auto stats = Fussion::Renderer2D::draw_stats();
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

        ImGui::PopStyleColor();
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

bool Editor::ViewportPanel::on_event(Fussion::Event &e)
{
    (void)e;
    return false;
}
