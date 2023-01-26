#include "Fussion/GCS/Transform.h"
#include "glm/gtc/type_ptr.hpp"
#include <imgui.h>

namespace Fussion
{
    void Transform::on_editor_gui()
    {
        ImGui::Text("Position:");
        ImGui::Columns(3, "position_columns", false);
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::DragFloat("##X", &m_position.x);
        ImGui::NextColumn();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &m_position.y);
        ImGui::NextColumn();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::DragFloat("##Z", &m_position.z);
        ImGui::Columns(1);

        if (ImGui::TreeNode("Scale")) {
            ImGui::DragFloat("X", &m_scale.x);
            ImGui::DragFloat("Y", &m_scale.y);
            ImGui::DragFloat("Z", &m_scale.z);
            ImGui::TreePop();
        }

        ImGui::AlignTextToFramePadding();
        ImGui::DragFloat("Rotation", &m_rotation);
    }
} // namespace Fussion
