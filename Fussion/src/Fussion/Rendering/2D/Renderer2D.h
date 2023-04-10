#pragma once
#include "Camera.h"
#include "Fussion/Rendering/Texture.h"

namespace Fussion::Renderer2D
{
    struct DrawStats {
        u32 draw_calls{0};
        u32 quad_count{0};

        mustuse u32 vertices() const { return quad_count * 4; }
    };

    // @Note We cant' use a mat because of the way
    // batch rendering works.
    struct DrawQuadParams {
        glm::vec3 position{0.f, 0.f, 0.f};
        /// Rotation in radians
        f32 rotation_radians{0.0f};
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec4 tint_color{1.f, 1.f, 1.f, 1.f};
        glm::vec2 uv_scale{1.f, 1.f};
        glm::mat4 parent_transform;
    };

    void init();
    void shutdown();

    void begin_scene(const Camera2D &camera, const glm::mat4 &transform);
    void end_scene();

    void draw_quad(const Ref<Texture> &texture, const DrawQuadParams &params);

    void flush();

    void start_batch();

    void reset_stats();

    DrawStats draw_stats();
} // namespace Fussion::Renderer2D
