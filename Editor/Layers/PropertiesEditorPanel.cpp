#include "PropertiesEditorPanel.h"
#include <Fussion/Scene/Components.h>
#include <ImGuiHelpers.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

using namespace Fussion;

void Editor::PropertiesEditorPanel::on_draw(Optional<Entity> selected, f32 delta)
{
    (void)delta;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(100, 100));
    ImGui::Begin("Properties");
    if (selected.has_value()) {
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Name");
        ImGui::SameLine();
        ImGui::InputText("##name", &selected->name().name);
        ImGui::Separator();

        // ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
        if (ImGui::TreeNodeEx("##transform", ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen,
                              "Transform")) {
            // ImGui::BeginChild("##inner_component", ImVec2(0, 0), true);
            // ImGuiHelpers::BeginGroupPanel("Transform", ImVec2(0, 0));

            // ImGui::Indent(10);

            ImGuiHelpers::BeginGroupPanel("Position", ImVec2(0, 0));
            ImGuiHelpers::DragVec3("##position", &selected->transform().position, 0.1f);
            ImGuiHelpers::EndGroupPanel();

            ImGuiHelpers::BeginGroupPanel("Rotation", ImVec2(0, 0));
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::DragFloat("##rotation", &selected->transform().rotation, 0.1f, 0.0f, 0.0f, "%.1f");
            ImGuiHelpers::EndGroupPanel();

            ImGuiHelpers::BeginGroupPanel("Scale", ImVec2(0, 0));
            ImGuiHelpers::DragVec3("##scale", &selected->transform().scale, 0.1f);
            ImGuiHelpers::EndGroupPanel();

            // ImGui::Unindent(10);

            // ImGui::EndChild();
            // ImGuiHelpers::EndGroupPanel();
        }
        // ImGui::PopStyleVar();
    }
    ImGui::End();
    ImGui::PopStyleVar();
}
