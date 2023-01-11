#include "Fussion/Application.hpp"
#include "Fussion/Rendering/Shader.hpp"
#include "Fussion/Rendering/Texture.hpp"
#include "Fussion/Rendering/VertexArray.hpp"

namespace fsn = fussion;

class Editor final : public fsn::Application
{
    Ptr<fsn::VertexArray> va {};
    Ptr<fsn::Shader> shader {};
    Ptr<fsn::Texture> container {};
    Ptr<fsn::Texture> container_specular {};

    void
    OnLoad() override;

    void OnUpdate(float delta) override;

    void OnEvent(const Ref<fsn::Event> &) override;

public:
    explicit Editor(const fussion::WindowProps &props) :
        Application(props) { }
};