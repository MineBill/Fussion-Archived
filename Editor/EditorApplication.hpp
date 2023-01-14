#include "Fussion/Application.h"
#include "Fussion/Math/Matrix4.h"
#include "Fussion/Math/Vector3.h"
#include "Fussion/Rendering/Shader.h"
#include "Fussion/Rendering/Texture.h"
#include "Fussion/Rendering/VertexArray.h"

namespace fsn = Fussion;

namespace Editor
{
    class EditorApplication final : public fsn::Application
    {
        Ref<fsn::VertexArray> va{};
        Ref<fsn::Shader> shader{};

        void OnLoad() override;

        void OnUpdate(float delta) override;

        void OnEvent(const Ref<fsn::Event> &) override;

        void Interface();

    public:
        explicit EditorApplication(const Fussion::WindowProps &props) : Application(props)
        {
        }
    };
} // namespace Editor
