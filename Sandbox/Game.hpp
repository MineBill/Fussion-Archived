#include <Fussion/Application.hpp>

namespace fsn = fussion;

class Game final : public fsn::Application {
    int count { 0 };

    void OnInitialize() override;

    void OnUpdate(f32 delta) override;

    void OnEvent(Ref<fsn::Event>) override;

public:
    Game() = default;
};