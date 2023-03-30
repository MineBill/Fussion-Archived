#pragma once
#include "Camera.h"
#include "Fussion/Rendering/Texture.h"

namespace Fussion::Renderer2D
{
    struct DrawStats {
        u32 Drawcalls{0};
        u32 QuadCount{0};

        mustuse u32 vertices() const { return QuadCount * 4; }
    };

    struct DrawQuadParams {
        glm::vec3 position{0.f, 0.f, 0.f};
        f32 rotation{0.0f};
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec4 tint_color{1.f, 1.f, 1.f, 1.f};
        glm::vec2 uv_scale{1.f, 1.f};
    };

    void init();
    void shutdown();

    void begin_scene(const Camera2D &camera, const glm::mat4 &transform);
    void end_scene();

    /* void draw_quad(const Ref<Texture> &texture, const glm::vec3 &position, const glm::vec3 &scale = {1, 1, 1},
                   const glm::vec2 &uvScale = {1, 1});

    void draw_quad_rotated(const Ref<Texture> &texture, const glm::vec3 &position, f32 rotation = 0.0f,
                           const glm::vec3 &scale = {1, 1, 1}, const glm::vec2 &uvScale = {1, 1}); */

    void draw_quad(const Ref<Texture> &texture, const DrawQuadParams &params);

    void flush();

    void start_batch();

    void reset_stats();

    DrawStats draw_stats();

    //    void DrawQuad(const Ref<Texture>& texture, const Transform2D);
} // namespace Fussion::Renderer2D
