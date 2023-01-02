#include <Fussion/Application.hpp>
#include <Fussion/Rendering/VertexArray.hpp>

namespace fsn = fussion;

class Game final : public fsn::Application {
    Ptr<fussion::VertexArray> va{};

    void on_initialize() override;

    void on_update(f32 delta) override;

    void on_event(Ref<fsn::Event>) override;

public:
    Game() = default;
};