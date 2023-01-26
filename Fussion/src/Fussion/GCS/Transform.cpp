#include "Fussion/GCS/Transform.h"
#include "glm/gtc/type_ptr.hpp"
#include <imgui.h>

namespace Fussion
{
    void Transform::OnEditorGUI()
    {
        ImGui::Text("Position:");
        ImGui::Columns(3, "position_columns", false);
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::DragFloat("##X", &Position.x);
        ImGui::NextColumn();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &Position.y);
        ImGui::NextColumn();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::DragFloat("##Z", &Position.z);
        ImGui::Columns(1);

        if (ImGui::TreeNode("Scale")) {
            ImGui::DragFloat("X", &Scale.x);
            ImGui::DragFloat("Y", &Scale.y);
            ImGui::DragFloat("Z", &Scale.z);
            ImGui::TreePop();
        }

        ImGui::AlignTextToFramePadding();
        ImGui::DragFloat("Rotation", &Rotation);
    }
} // namespace Fussion
