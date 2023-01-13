#include "Fussion/Application.hpp"
#include "Fussion/Input/Keys.hpp"
#include "Fussion/Layers/ImGuiImpl.hpp"
#include "Fussion/Math/Matrix4.hpp"
#include "Fussion/Rendering/Shader.hpp"
#include "Fussion/Rendering/VertexArray.hpp"
#include "Fussion/Rendering/VertexBuffer.hpp"
#include "Fussion/Types.hpp"
#include "imgui.h"
#include <assert.hpp>
#include <cmath>
#include <glad/glad.h>
#include <tuple>

struct OpenGLState {
    i32 prevVao {};
    i32 prevArrayBuffer {};
    i32 prevProgram {};
    i32 prevBlendEnabled {};
    i32 prevScissorTestEnabled {};
    i32 prevBlendEquationRgb {};
    i32 prevBlendEquationAlpha {};
    i32 prevBlendFuncSrcRgb {};
    i32 prevBlendFuncSrcAlpha {};
    i32 prevBlendFuncDstRgb {};
    i32 prevBlendFuncDstAlpha {};
    i32 prevCullFaceEnabled {};
    i32 prevDepthTestEnabled {};
    i32 prevActiveTexture {};
    i32 prevTexture2D {};

    OpenGLState()
    {
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prevVao);
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prevArrayBuffer);
        glGetIntegerv(GL_CURRENT_PROGRAM, &prevProgram);
        glGetIntegerv(GL_BLEND, &prevBlendEnabled);
        glGetIntegerv(GL_SCISSOR_TEST, &prevScissorTestEnabled);
        glGetIntegerv(GL_BLEND_EQUATION_RGB, &prevBlendEquationRgb);
        glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &prevBlendEquationAlpha);
        glGetIntegerv(GL_BLEND_SRC_RGB, &prevBlendFuncSrcRgb);
        glGetIntegerv(GL_BLEND_SRC_ALPHA, &prevBlendFuncSrcAlpha);
        glGetIntegerv(GL_BLEND_DST_RGB, &prevBlendFuncDstRgb);
        glGetIntegerv(GL_BLEND_DST_ALPHA, &prevBlendFuncDstAlpha);
        glGetIntegerv(GL_CULL_FACE, &prevCullFaceEnabled);
        glGetIntegerv(GL_DEPTH_TEST, &prevDepthTestEnabled);
        glGetIntegerv(GL_ACTIVE_TEXTURE, &prevActiveTexture);
        glActiveTexture(GL_TEXTURE0);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &prevTexture2D);
    }

    ~OpenGLState()
    {
        glBindTexture(GL_TEXTURE_2D, static_cast<u32>(prevTexture2D));
        glActiveTexture(static_cast<u32>(prevActiveTexture));
        glUseProgram(static_cast<u32>(prevProgram));
        glBindVertexArray(static_cast<u32>(prevVao));
        // glScissor(prevScissorBox[0], prevScissorBox[1], prevScissorBox[2], prevScissorBox[3]);
        glBindBuffer(GL_ARRAY_BUFFER, static_cast<u32>(prevArrayBuffer));
        glBlendEquationSeparate(static_cast<u32>(prevBlendEquationRgb), static_cast<u32>(prevBlendEquationAlpha));
        glBlendFuncSeparate(
            static_cast<u32>(prevBlendFuncSrcRgb),
            static_cast<u32>(prevBlendFuncDstRgb),
            static_cast<u32>(prevBlendFuncSrcAlpha),
            static_cast<u32>(prevBlendFuncDstAlpha));

        if (prevBlendEnabled) {
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }

        if (prevDepthTestEnabled) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }

        if (prevCullFaceEnabled) {
            glEnable(GL_CULL_FACE);
        } else {
            glDisable(GL_CULL_FACE);
        }

        if (prevScissorTestEnabled) {
            glEnable(GL_SCISSOR_TEST);
        } else {
            glDisable(GL_SCISSOR_TEST);
        }
    }
};

constexpr auto VertexSource
    = R"(#version 330 core

uniform mat4 projection_matrix;

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_texCoord;
layout(location = 2) in vec4 in_color;

out vec4 color;
out vec2 texCoord;

void main()
{
    gl_Position = projection_matrix * vec4(in_position, 0, 1);
    color = in_color;
    texCoord = in_texCoord;
})";

constexpr auto FragmentSource = R"(#version 330 core

uniform sampler2D in_fontTexture;

in vec4 color;
in vec2 texCoord;

out vec4 outputColor;

void main()
{
    outputColor = color * texture(in_fontTexture, texCoord);
})";

using namespace fussion;

class ImGuiImplFussion : public ImGuiImpl
{
    std::pair<i32, i32> m_window_size {};
    ImGuiContext *m_context { nullptr };
    bool m_frame_begun { false };
    Ptr<Shader> m_shader {};
    Ptr<VertexArray> m_va {};

    i32 vertex_buffer_size {};
    i32 index_buffer_size {};

public:
    ImGuiImplFussion(i32 width, i32 height) :
        m_window_size { width, height }
    {
        m_context = ImGui::CreateContext();
        ImGui::SetCurrentContext(m_context);

        auto &io = ImGui::GetIO();

        io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
        io.Fonts->AddFontDefault();

        CreateDeviceResources();
        SetKeyMappings();

        SetPerFrameImGuiData(1.0f / 144.0f);
        ImGui::NewFrame();
        m_frame_begun = true;
    }

    void NewFrame(f32 elapsed) override
    {
        if (m_frame_begun) {
            ImGui::Render();
        }

        SetPerFrameImGuiData(elapsed);
        UpdateImGuiInput();

        m_frame_begun = true;
        ImGui::NewFrame();
    }

    void SetPerFrameImGuiData(f32 elapsed)
    {
        auto &io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<f32>(m_window_size.first);
        io.DisplaySize.y = static_cast<f32>(m_window_size.second);

//                io.DisplayFramebufferScale = 1.0f;
        io.DeltaTime = elapsed;
    }

    void UpdateImGuiInput()
    {
        //        auto &app = Application::GetInstance();
    }

    void Render() override
    {
        if (m_frame_begun) {
            m_frame_begun = false;
            ImGui::Render();
            RenderImDrawData(ImGui::GetDrawData());
        }
    }

    void WindowResized(i32 width, i32 height) override
    {
        m_window_size = { width, height };
    }

    void CreateDeviceResources()
    {
        vertex_buffer_size = 10000;
        index_buffer_size = 2000;
        using enum VertexType;
        m_va = VertexArray::WithSize(vertex_buffer_size, index_buffer_size, { Vector2, Vector2, Vector4 });
        m_shader = Shader::FromStringLiterals(VertexSource, FragmentSource);

        RecreateFontDeviceTexture();
    }

    void RecreateFontDeviceTexture()
    {
        auto &io = ImGui::GetIO();
        u8 *pixels;
        i32 width;
        i32 height;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

        auto texture = Texture::FromPixels(pixels, width, height);

        // int mips = floorf(logf(std::max(width, height), 2));
        texture->Use(0);

        io.Fonts->SetTexID
            (reinterpret_cast<ImTextureID>(static_cast<intptr_t>(texture->Handle())));
        io.Fonts->ClearTexData();
    }

    void SetKeyMappings()
    {
        auto &io = ImGui::GetIO();
        io.KeyMap[ImGuiKey_Tab] = static_cast<i32>(Key::Tab);
        io.KeyMap[ImGuiKey_LeftArrow] = static_cast<i32>(Key::Left);
        io.KeyMap[ImGuiKey_RightArrow] = static_cast<i32>(Key::Right);
        io.KeyMap[ImGuiKey_UpArrow] = static_cast<i32>(Key::Up);
        io.KeyMap[ImGuiKey_DownArrow] = static_cast<i32>(Key::Down);
        io.KeyMap[ImGuiKey_PageUp] = static_cast<i32>(Key::PageUp);
        io.KeyMap[ImGuiKey_PageDown] = static_cast<i32>(Key::PageDown);
        io.KeyMap[ImGuiKey_Home] = static_cast<i32>(Key::Home);
        io.KeyMap[ImGuiKey_End] = static_cast<i32>(Key::End);
        io.KeyMap[ImGuiKey_Delete] = static_cast<i32>(Key::Delete);
        io.KeyMap[ImGuiKey_Backspace] = static_cast<i32>(Key::Backspace);
        io.KeyMap[ImGuiKey_Enter] = static_cast<i32>(Key::Enter);
        io.KeyMap[ImGuiKey_Escape] = static_cast<i32>(Key::Escape);
        io.KeyMap[ImGuiKey_CapsLock] = static_cast<i32>(Key::CapsLock);
        io.KeyMap[ImGuiKey_LeftCtrl] = static_cast<i32>(Key::LeftControl);
        io.KeyMap[ImGuiKey_RightCtrl] = static_cast<i32>(Key::RightControl);
        io.KeyMap[ImGuiKey_LeftShift] = static_cast<i32>(Key::LeftShift);
        io.KeyMap[ImGuiKey_RightShift] = static_cast<i32>(Key::RightShift);
        io.KeyMap[ImGuiKey_LeftAlt] = static_cast<i32>(Key::LeftAlt);
        io.KeyMap[ImGuiKey_RightAlt] = static_cast<i32>(Key::RightAlt);
        io.KeyMap[ImGuiKey_A] = static_cast<i32>(Key::A);
        io.KeyMap[ImGuiKey_B] = static_cast<i32>(Key::B);
        io.KeyMap[ImGuiKey_C] = static_cast<i32>(Key::C);
        io.KeyMap[ImGuiKey_D] = static_cast<i32>(Key::D);
        io.KeyMap[ImGuiKey_E] = static_cast<i32>(Key::E);
        io.KeyMap[ImGuiKey_F] = static_cast<i32>(Key::F);
        io.KeyMap[ImGuiKey_G] = static_cast<i32>(Key::G);
        io.KeyMap[ImGuiKey_H] = static_cast<i32>(Key::H);
        io.KeyMap[ImGuiKey_I] = static_cast<i32>(Key::I);
        io.KeyMap[ImGuiKey_J] = static_cast<i32>(Key::J);
        io.KeyMap[ImGuiKey_K] = static_cast<i32>(Key::K);
        io.KeyMap[ImGuiKey_L] = static_cast<i32>(Key::L);
        io.KeyMap[ImGuiKey_M] = static_cast<i32>(Key::M);
        io.KeyMap[ImGuiKey_N] = static_cast<i32>(Key::N);
        io.KeyMap[ImGuiKey_O] = static_cast<i32>(Key::O);
        io.KeyMap[ImGuiKey_P] = static_cast<i32>(Key::P);
        io.KeyMap[ImGuiKey_Q] = static_cast<i32>(Key::Q);
        io.KeyMap[ImGuiKey_R] = static_cast<i32>(Key::R);
        io.KeyMap[ImGuiKey_S] = static_cast<i32>(Key::S);
        io.KeyMap[ImGuiKey_T] = static_cast<i32>(Key::T);
        io.KeyMap[ImGuiKey_U] = static_cast<i32>(Key::U);
        io.KeyMap[ImGuiKey_V] = static_cast<i32>(Key::V);
        io.KeyMap[ImGuiKey_W] = static_cast<i32>(Key::W);
        io.KeyMap[ImGuiKey_X] = static_cast<i32>(Key::X);
        io.KeyMap[ImGuiKey_Y] = static_cast<i32>(Key::Y);
        io.KeyMap[ImGuiKey_Z] = static_cast<i32>(Key::Z);
    }

    void RenderImDrawData(ImDrawData *data)
    {
        if (data->CmdListsCount == 0) {
            return;
        }
        OpenGLState state {};

        m_va->Use();

        for (int i = 0; i < data->CmdListsCount; i++) {
            const auto *cmdList = data->CmdLists[i];

            auto vertex_size = cmdList->VtxBuffer.Size * static_cast<i32>(sizeof(ImDrawVert));
            if (vertex_size > vertex_buffer_size) {
                auto new_size = static_cast<i32>(std::max(static_cast<f32>(vertex_buffer_size) * 1.5f, static_cast<f32>(vertex_size)));
                m_va->ResizeVertexBuffer(new_size);
                vertex_buffer_size = new_size;
            }

            auto index_size = cmdList->IdxBuffer.Size * static_cast<i32>(sizeof(ImDrawIdx));
            if (index_size > index_buffer_size) {
                auto new_size = static_cast<i32>(std::max(static_cast<f32>(index_buffer_size) * 1.5f, static_cast<f32>(index_size)));
                m_va->ResizeIndexBuffer(new_size);
                index_buffer_size = new_size;
            }
        }

        const auto &io = ImGui::GetIO();
        auto mvp = Matrix4::CreateOrthographicOffCenter(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, 1.0f);

        m_shader->SetUniform("projection_matrix", mvp);
        m_shader->SetUniform("in_fontTexture", 0);

        data->ScaleClipRects(io.DisplayFramebufferScale);

        glEnable(GL_BLEND);
        glEnable(GL_SCISSOR_TEST);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        for (auto i = 0; i < data->CmdListsCount; i++) {
            auto *draw_list = data->CmdLists[i];

            // draw_list->VtxBuffer.Size;
            m_va->UpdateVertexBufferSubData(0, draw_list->VtxBuffer.Data, draw_list->VtxBuffer.Size);
            m_va->UpdateIndexBufferSubData(0, draw_list->IdxBuffer.Data, draw_list->IdxBuffer.Size);

            for (auto k = 0; k < draw_list->CmdBuffer.Size; k++) {
                auto draw_cmd = draw_list->CmdBuffer[k];
                ASSERT(draw_cmd.UserCallback == nullptr, "NotImplementedException");

                glActiveTexture(GL_TEXTURE0);
                auto id = static_cast<u32>(reinterpret_cast<intptr_t>(draw_cmd.TextureId));
                glBindTexture(GL_TEXTURE_2D, id);

                auto clip = draw_cmd.ClipRect;
                glScissor(
                    static_cast<i32>(clip.x),
                    std::get<1>(m_window_size) - static_cast<i32>(clip.w),
                    static_cast<i32>(clip.z - clip.x),
                    static_cast<i32>(clip.w - clip.y));

                if ((io.BackendFlags & ImGuiBackendFlags_RendererHasVtxOffset) != 0) {
                    glDrawElementsBaseVertex(
                        GL_TRIANGLES,
                        static_cast<i32>(draw_cmd.ElemCount),
                        GL_UNSIGNED_SHORT,
                        reinterpret_cast<void *>(draw_cmd.IdxOffset * sizeof(ushort)), // NOLINT(performance-no-int-to-ptr)
                        static_cast<i32>(draw_cmd.VtxOffset));
                } else {
                    glDrawElements(GL_TRIANGLES, static_cast<i32>(draw_cmd.ElemCount), GL_UNSIGNED_SHORT, reinterpret_cast<void*>(draw_cmd.IdxOffset * sizeof(ushort)));
                }
            }
        }

        glDisable(GL_BLEND);
        glDisable(GL_SCISSOR_TEST);
    }
};

Ptr<ImGuiImpl> ImGuiImpl::Create(i32 width, i32 height)
{
    return std::make_unique<ImGuiImplFussion>(width, height);
}
