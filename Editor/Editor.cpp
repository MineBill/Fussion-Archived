#include "Editor.hpp"
#include "CubeData.hpp"
#include "Fussion/Rendering/Texture.hpp"
#include <Fussion/Events/ApplicationEvents.hpp>
#include <Fussion/Math/Vector3.hpp>
#include <glad/glad.h>
#include <iostream>

using namespace fussion;

void Editor::OnLoad()
{
    using enum fussion::VertexType;
    va = VertexArray::Create(CUBE_DATA, { Vector3, Vector2, Vector3 });
    shader = Shader::Create("Resources/simple.vert", "Resources/simple.frag");
    container = Texture::LoadFromFile("Resources/container2.png");
    container_specular = Texture::LoadFromFile("Resources/container2_specular.png");
    glClearColor(1.0f, 0, 0, 1.0f);
}

void Editor::OnUpdate(float)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    va->Use();

    container->Use(0);
    shader->SetUniform("uMaterial.diffuse", 0);

    container_specular->Use(1);
    shader->SetUniform("uMaterial.specular", 1);
}

void Editor::OnEvent(const Ref<Event> &event)
{
    fsn::Dispatcher dispatcher(event);
    dispatcher.DispatchNoConsume<WindowResized>([](const Ref<WindowResized> &window_resized) {
        std::cout << window_resized->ToString() << '\n';
    });
}