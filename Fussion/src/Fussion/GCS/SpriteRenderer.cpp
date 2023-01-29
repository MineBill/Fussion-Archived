#include "Fussion/GCS/SpriteRenderer.h"
#include <ImGuiFileDialog.h>
#include <imgui.h>

namespace Fussion
{
    void SpriteRenderer::on_update(f32)
    {
        if (!m_sprite) {
            return;
        }
        FSN_CORE_ASSERT(owner() != nullptr);

        auto transform = owner()->transform();
        Renderer2D::draw_quad(m_sprite, transform->position(), transform->scale(), m_texture_coordinates);
    }

    void SpriteRenderer::on_editor_gui()
    {
        if (ImGui::TreeNode("Texture")) {
            ImGui::Text("ID: [%s]", m_sprite ? std::to_string(m_sprite->renderer_handle()).c_str() : "null");
            if (m_sprite) {
                ImTextureID texture = reinterpret_cast<ImTextureID>(m_sprite->renderer_handle()); // NOLINT
                ImGui::Image(texture, {100, 100});
            }

            if (ImGui::Button("Load Texture From File"))
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".png,.jpg", ".");

            // display
            if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
                // action if OK
                if (ImGuiFileDialog::Instance()->IsOk()) {
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

                    FSN_CORE_LOG("Loading texture from {}", filePathName);
                    m_sprite = Texture::LoadFromFile(filePathName);
                    FSN_CORE_LOG("LOL");
                }

                // close
                ImGuiFileDialog::Instance()->Close();
            }
            ImGui::TreePop();
        }
    }

    void SpriteRenderer::set_texture(const Ref<Texture> &new_texture)
    {
        m_sprite = new_texture;
    }
} // namespace Fussion
