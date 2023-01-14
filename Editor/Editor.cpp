#include "Editor.hpp"
#include "CubeData.hpp"
#include "Fussion/Rendering/Texture.h"
#include "Fussion/Rendering/VertexBuffer.h"
#include <Fussion/Events/ApplicationEvents.h>
#include <Fussion/Events/KeyboardEvents.h>
#include <Fussion/Math/Vector3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <iostream>
#include <spdlog/spdlog.h>

using namespace fussion;
using namespace editor;

void Editor::OnLoad()
{
    using enum fussion::VertexType;
    va = VertexArray::Create(CUBE_DATA, { Vector3, Vector2, Vector3 });

    shader = Shader::Create("Resources/simple.vert", "Resources/simple.frag");
    container = Texture::LoadFromFile("Resources/container2.png");
    container_specular = Texture::LoadFromFile("Resources/container2_specular.png");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    glClearColor(0.83f, 0.79f, 0.94f, 1.0f);
}

void Editor::OnUpdate(float)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    va->Use();

    container->Use(0);
    shader->SetUniform("uMaterial.diffuse", 0);

    container_specular->Use(1);
    shader->SetUniform("uMaterial.specular", 1);
    shader->SetUniform("uMaterial.shininess", 32.0f);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    Interface();
}

void Editor::OnEvent(const Ref<Event> &event)
{
    fsn::Dispatcher dispatcher(event);
    dispatcher.DispatchNoConsume<WindowResized>([](const Ref<WindowResized> &window_resized) {
        glViewport(0, 0, window_resized->Width(), window_resized->Height());
        std::cout << window_resized->ToString() << ':' << window_resized->Width() << '\n';
    });

    dispatcher.Dispatch<OnKeyPressed>([this](const Ref<OnKeyPressed> &key_pressed) {
        if (key_pressed->GetKey() == Key::Escape) {
            Quit();
        }
    });
}

void Editor::Interface()
{
    auto flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), flags);
    ImGui::Begin("LOL");
    ImGui::End();
    ImGui::ShowDemoWindow();
}
