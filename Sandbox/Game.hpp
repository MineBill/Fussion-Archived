#include <Fussion/Application.hpp>

namespace fsn = fussion;

class Game final : public fsn::Application {
    int count { 0 };

    void OnInitialize() override;

    void OnUpdate() override;

    void OnEvent() override;

public:
    Game() = default;
};