#include "Fussion/Application.h"
#include "Fussion/Math/Matrix4.h"
#include "Fussion/Math/Vector3.h"
#include "Fussion/Rendering/Camera.h"
#include "Fussion/Rendering/Shader.h"
#include "Fussion/Rendering/Texture.h"
#include "Fussion/Rendering/VertexArray.h"

namespace Editor
{
    class EditorApplication final : public Fussion::Application
    {
        Ref<Fussion::VertexArray> va{};
        Ref<Fussion::VertexArray> blueVA{};

        Ref<Fussion::Shader> shader{};
        Ref<Fussion::Shader> blueShader{};

        Ptr<Fussion::Camera2D> m_camera;

        void OnLoad() override;

        void OnUpdate(f32 delta) override;

        void OnEvent(Fussion::Event &) override;

        void Interface(f32);

    public:
        explicit EditorApplication(const Fussion::WindowProps &props) : Application(props) {}
    };
} // namespace Editor
