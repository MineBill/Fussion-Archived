#include "Fussion/Application.hpp"
#include "Fussion/Math/Matrix4.hpp"
#include "Fussion/Math/Vector3.hpp"
#include "Fussion/Rendering/Shader.hpp"
#include "Fussion/Rendering/Texture.hpp"
#include "Fussion/Rendering/VertexArray.hpp"

namespace fsn = fussion;

namespace editor
{

class Editor final : public fsn::Application
{
    Ptr<fsn::VertexArray> va {};
    Ptr<fsn::Shader> shader {};
    Ptr<fsn::Texture> container {};
    Ptr<fsn::Texture> container_specular {};
    Matrix camera_perspective {};

    void OnLoad() override;

    void OnUpdate(float delta) override;

    void OnEvent(const Ref<fsn::Event> &) override;

    void Interface();

public:
    explicit Editor(const fussion::WindowProps &props) :
        Application(props) { }
};

}
