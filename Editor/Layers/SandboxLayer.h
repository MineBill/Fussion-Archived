#pragma once
#include <Fussion/Fussion.h>

class SandboxLayer : public Fussion::Layer
{
    Fussion::Ptr<Fussion::Camera2DController> m_camera;
    Fussion::Ref<Fussion::Texture> m_texture, m_second_texture;
    Fussion::Ref<Fussion::Framebuffer> m_frameBuffer{};

    glm::vec3 m_first_position, m_second_position;
    glm::vec3 m_clearColor{0.816f, 0.828f, 0.828f};
    glm::vec2 m_viewportSize{};

    void Interface(f32);

public:
    ~SandboxLayer() override = default;
    void on_load() override;
    void on_update(f32 f321) override;
    bool on_event(Fussion::Event &event) override;
};
