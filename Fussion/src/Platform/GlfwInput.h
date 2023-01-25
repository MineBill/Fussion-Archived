#pragma once
#include "Fussion/Input/Input.h"

namespace Fussion
{
    class GlfwInput final : public Input
    {
    public:
        enum class KeyState {
            None = 0,
            Down,
            Up,
            JustReleased,
        };

    private:
        std::unordered_map<Key, KeyState> m_key_cache{};
        std::unordered_map<Key, KeyState> m_key_cache_previous{};

    protected:
        mustuse glm::vec2 GetMouseImpl() override;
        mustuse bool IsKeyDownImpl(Key key) override;
        mustuse bool IsKeyUpImpl(Key key) override;
        mustuse bool IsKeyJustPressedImpl(Key key) override;

        void SetMousePositionImpl(u32 x, u32 y) override;
        void FlushImpl() override;

    public:
        ~GlfwInput() override = default;
    };
} // namespace Fussion
