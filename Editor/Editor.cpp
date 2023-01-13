#include "Editor.hpp"
#include "CubeData.hpp"
#include "Fussion/Components/Transform.hpp"
#include "Fussion/GameObject.hpp"
#include "Fussion/Rendering/Texture.hpp"
#include "Fussion/Rendering/VertexBuffer.hpp"
#include <Fussion/Events/ApplicationEvents.hpp>
#include <Fussion/Events/KeyboardEvents.hpp>
#include <Fussion/Math/Vector3.hpp>
#include <glad/glad.h>
#include <imgui.h>
#include <iostream>

using namespace fussion;
using namespace editor;

void Editor::OnLoad()
{
    using enum fussion::VertexType;
    va = VertexArray::Create(CUBE_DATA, { Vector3, Vector2, Vector3 });

    shader = Shader::Create("Resources/simple.vert", "Resources/simple.frag");
    container = Texture::LoadFromFile("Resources/container2.png");
    container_specular = Texture::LoadFromFile("Resources/container2_specular.png");

    auto size = GetWindow().Size();
    camera_perspective = Matrix4::CreatePerspectiveFieldOfView(1.047198f, static_cast<f32>(size.first) / static_cast<f32>(size.second), 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    glClearColor(0.83f, 0.79f, 0.94f, 1.0f);

//    camera = Transform {
//        .position = fsn::Vector3(0.0f),
//        .rotation = fsn::Vector3(0.f, 0.f, 0.f),
//        .scale = fsn::Vector3(1.0f),
//    };
//    go.AddComponent<Transform>();
//
//    cube = Transform {
//        .position = fsn::Vector3(1.0f),
//        .rotation = fsn::Vector3(10.f, 0.f, 0.f),
//        .scale = fsn::Vector3(1.0f),
//    };
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

    shader->SetUniform("uProjectionMatrix", camera_perspective);
//    shader->SetUniform("uCamaraPosition", camera.position);
//    shader->SetUniform("uViewMatrix", camera.Model());
//
//    shader->SetUniform("uModelMatrix", cube.Model());
    glDrawArrays(GL_TRIANGLES, 0, 36);
//    camera.position.x() += 0.01f;

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
