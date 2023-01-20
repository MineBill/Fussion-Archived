#pragma once
#include "Camera.h"
#include "Fussion/Rendering/Texture.h"

namespace Fussion::Renderer2D
{
    void Init();
    void Shutdown();

    void BeginScene(const Camera2D &camera);
    void EndScene();

    void DrawQuad(const Ref<Texture> &texture, const glm::vec3 &position, f32 rotation = 0.0f,
                  const glm::vec3 &scale = {1, 1, 1}, const glm::vec2 &uvScale = {1, 1});

    void Flush();

    //    void DrawQuad(const Ref<Texture>& texture, const Transform2D);
} // namespace Fussion::Renderer2D
