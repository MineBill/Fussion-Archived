#include "PropertiesEditorPanel.h"
#include "glm/gtc/type_ptr.hpp"
#include <Fussion/Scene/Components.h>
#include <ImGuiFileDialog.h>
#include <ImGuiHelpers.h>
#include <filesystem>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

using namespace Fussion;

void Editor::PropertiesEditorPanel::on_draw(Optional<Entity> selected, f32 delta)
{
    m_selected_entity = selected;
    (void)delta;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(100, 100));
    ImGui::Begin("Properties");
    if (selected.has_value()) {
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Name");
        ImGui::SameLine();
        ImGui::InputText("##name", &selected->name().name);
        ImGui::Separator();

        transform_component_gui();
        sprite_component_gui();
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

void Editor::PropertiesEditorPanel::sprite_component_gui()
{
    if (auto *sprite = m_selected_entity->get_component_or_null<SpriteComponent>()) {
        if (ImGui::TreeNodeEx("##sprite_component", ImGuiTreeNodeFlags_CollapsingHeader, "SpriteComponent")) {
            ImGui::Indent(10);

            ImGui::AlignTextToFramePadding();
            auto w = ImGui::GetContentRegionAvail().x;
            ImGui::Text("Texture");
            ImGui::SameLine(w / 2.0f);
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            // @NOTE Maybe this is stupid?
            auto string = fmt::format("Handle: {}", sprite->texture->renderer_handle());
            ImGui::InputText("##texture_handle", &string, ImGuiInputTextFlags_ReadOnly);

            ImGui::Text("Color Tint");
            ImGui::SameLine();
            ImGui::ColorEdit4("##tint_color", glm::value_ptr(sprite->tint_color));

            if (ImGuiHelpers::ButtonCenteredOnLine("Load Texture")) {
                ImGuiFileDialog::Instance()->OpenDialog("LoadTextureFileDialog", "Choose a texture", ".png,.jpg", ".");
            }

            if (ImGuiFileDialog::Instance()->Display("LoadTextureFileDialog")) {
                if (ImGuiFileDialog::Instance()->IsOk()) {
                    namespace fs = std::filesystem;
                    fs::path name = ImGuiFileDialog::Instance()->GetFilePathName();
                    fs::path path = ImGuiFileDialog::Instance()->GetCurrentPath();

                    sprite->texture = Texture::load_from_file(path / name);
                }
                ImGuiFileDialog::Instance()->Close();
            }
            ImGui::Unindent();
            ImGui::Separator();
        }
    }
}

void Editor::PropertiesEditorPanel::transform_component_gui()
{
    if (ImGui::TreeNodeEx("##transform", ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen,
                          "Transform")) {
        ImGuiHelpers::BeginGroupPanel("Position", ImVec2(0, 0));
        ImGuiHelpers::DragVec3("##position", &m_selected_entity->transform().position, 0.1f);
        ImGuiHelpers::EndGroupPanel();

        ImGuiHelpers::BeginGroupPanel("Rotation", ImVec2(0, 0));
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::DragFloat("##rotation", &m_selected_entity->transform().rotation, 0.1f, 0.0f, 0.0f, "%.1f");
        ImGuiHelpers::EndGroupPanel();

        ImGuiHelpers::BeginGroupPanel("Scale", ImVec2(0, 0));
        ImGuiHelpers::DragVec3("##scale", &m_selected_entity->transform().scale, 0.1f);
        ImGuiHelpers::EndGroupPanel();
    }
}
