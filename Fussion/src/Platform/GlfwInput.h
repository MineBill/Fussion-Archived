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
        mustuse glm::vec2 mouse_impl() override;
        mustuse bool is_key_down_impl(Key key) override;
        mustuse bool is_key_up_impl(Key key) override;
        mustuse bool is_key_just_pressed_impl(Key key) override;

        void set_mouse_impl(u32 x, u32 y) override;
        void flush_impl() override;

    public:
        ~GlfwInput() override = default;
    };
} // namespace Fussion
