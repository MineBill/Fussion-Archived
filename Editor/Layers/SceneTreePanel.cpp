#include "SceneTreePanel.h"
#include <Fussion/Scene/Components.h>
#include <Fussion/Scene/Entity.h>
#include <imgui.h>

Editor::SceneTreePanel::SceneTreePanel() : m_selected_entity()
{
}

namespace
{
    [[maybe_unused]] void HelpMarker(const char *desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

} // namespace

void Editor::SceneTreePanel::render_entity(Fussion::Scene &scene, Fussion::Entity e) // NOLINT
{
    auto &name = e.get_component<Fussion::NameComponent>();
    ImGuiTreeNodeFlags flags =
        ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow;

    Fussion::ChildrenComponent *children_component{nullptr};
    if (e.has_component<Fussion::ChildrenComponent>()) {
        children_component = &e.get_component<Fussion::ChildrenComponent>();
    }
    if (children_component == nullptr || children_component->children.empty()) {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }
    if (m_selected_entity == e) {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    void *id = reinterpret_cast<void *>(e.id()); // NOLINT
    ImGui::PushID(id);
    bool opened = ImGui::TreeNodeEx(id, flags, "%s", name.name.c_str());
    ImGui::PopID();

    if (ImGui::IsItemClicked()) {
        m_selected_entity = e;
    }

    // Context menu
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
    if (ImGui::BeginPopupContextItem()) {
        if (ImGui::MenuItem("Add child")) {
            auto new_go = scene.create("New Entity");
            e.add_child(new_go);
        }
        ImGui::SameLine();
        HelpMarker("Create a new entity as a child.");

        if (ImGui::MenuItem("Destroy")) {
            e.destroy();
            FSN_CORE_LOG("Destroy {} id: {}", e.name().name, static_cast<u64>(e.id()));
        }
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();

    ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - ImGui::CalcTextSize("(?)").x);
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
        ImGui::BeginTooltip();
        ImGui::Text("Entity: %d", e.entity_id());
        ImGui::Text("Version: %d", e.version());
        ImGui::EndTooltip();
    }

    if (opened) {
        if (children_component) {
            for (auto &child : children_component->children) {
                render_entity(scene, child);
            }
        }
        ImGui::TreePop();
    }
}

void Editor::SceneTreePanel::on_draw(Fussion::Scene &scene, f32 delta)
{
    auto &reg = scene.registry();
    (void)delta;
    ImGui::Begin("Scene Tree");

    if (ImGui::Button("New Entity")) {
        scene.create("New Entity").add_component<Fussion::ChildrenComponent>(std::vector<Fussion::Entity>());
    }
    ImGui::Separator();
    reg.each([&](entt::entity entity) {
        Fussion::Entity e(entity, &scene);
        if (e.has_component<Fussion::ChildrenComponent>() && !e.has_component<Fussion::ParentComponent>()) {
            render_entity(scene, e);
        }
    });
    ImGui::End();
}
