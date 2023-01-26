#pragma once
#include "Fussion/Events/Event.h"
#include "Keys.h"

namespace Fussion
{
    class Input
    {
        friend class Application;
        static Ptr<Input> s_input;

    protected:
        mustuse virtual glm::vec2 mouse_impl() = 0;
        mustuse virtual bool is_key_down_impl(Key key) = 0;
        mustuse virtual bool is_key_up_impl(Key key) = 0;
        mustuse virtual bool is_key_just_pressed_impl(Key key) = 0;
        virtual void set_mouse_impl(u32 x, u32 y) = 0;
        virtual void flush_impl() = 0;

    public:
        virtual ~Input() = default;

        mustuse static glm::vec2 mouse()
        {
            return s_input->mouse_impl();
        }

        mustuse static bool is_key_down(Key key)
        {
            return s_input->is_key_down_impl(key);
        }

        mustuse static bool is_key_up(Key key)
        {
            return s_input->is_key_up_impl(key);
        }

        mustuse static bool is_key_just_pressed(Key key)
        {
            return s_input->is_key_just_pressed_impl(key);
        }

        mustuse static f32 axis(Key positive, Key negative)
        {
            return static_cast<f32>(s_input->is_key_down_impl(positive)) -
                   static_cast<f32>(s_input->is_key_down_impl(negative));
        }

        mustuse static glm::vec2 vector(Key x_positive, Key x_negative, Key y_positive, Key y_negative)
        {
            return {
                axis(x_positive, x_negative),
                axis(y_positive, y_negative),
            };
        }

        static void set_mouse(u32 x, u32 y)
        {
            s_input->set_mouse_impl(x, y);
        }

    private:
        static void flush()
        {
            s_input->flush_impl();
        }
    };
} // namespace Fussion
