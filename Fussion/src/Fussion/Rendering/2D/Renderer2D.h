#pragma once
#include "Camera.h"
#include "Fussion/Rendering/Texture.h"

namespace Fussion::Renderer2D
{
    struct DrawStats {
        u32 Drawcalls{0};
        u32 QuadCount{0};

        u32 GetVertices() const
        {
            return QuadCount * 4;
        }
    };

    void Init();
    void Shutdown();

    void BeginScene(const Camera2D &camera);
    void EndScene();

    void DrawQuad(const Ref<Texture> &texture, const glm::vec3 &position, const glm::vec3 &scale = {1, 1, 1},
                  const glm::vec2 &uvScale = {1, 1});

    void DrawQuadRotated(const Ref<Texture> &texture, const glm::vec3 &position, f32 rotation = 0.0f,
                         const glm::vec3 &scale = {1, 1, 1}, const glm::vec2 &uvScale = {1, 1});

    void Flush();

    void StartBatch();

    void ResetStats();

    DrawStats GetDrawStats();

    //    void DrawQuad(const Ref<Texture>& texture, const Transform2D);
} // namespace Fussion::Renderer2D
