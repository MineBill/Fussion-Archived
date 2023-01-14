#include "Fussion/Application.h"
#include "Fussion/EntityComponent.hpp"
#include "Fussion/Math/Matrix4.h"
#include "Fussion/Math/Vector3.h"
#include "Fussion/Rendering/Shader.h"
#include "Fussion/Rendering/Texture.h"
#include "Fussion/Rendering/VertexArray.h"

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
    fsn::ecs::Manager m_manager{};

    void OnLoad() override;

    void OnUpdate(float delta) override;

    void OnEvent(const Ref<fsn::Event> &) override;

    void Interface();

public:
    explicit Editor(const fussion::WindowProps &props) :
        Application(props) { }
};

}
