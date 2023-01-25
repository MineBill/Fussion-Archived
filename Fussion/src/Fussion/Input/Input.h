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
        mustuse virtual glm::vec2 GetMouseImpl() = 0;
        mustuse virtual bool IsKeyDownImpl(Key key) = 0;
        mustuse virtual bool IsKeyUpImpl(Key key) = 0;
        mustuse virtual bool IsKeyJustPressedImpl(Key key) = 0;
        virtual void SetMousePositionImpl(u32 x, u32 y) = 0;
        virtual void FlushImpl() = 0;

    public:
        virtual ~Input() = default;

        mustuse static glm::vec2 GetMouse()
        {
            return s_input->GetMouseImpl();
        }

        mustuse static bool IsKeyDown(Key key)
        {
            return s_input->IsKeyDownImpl(key);
        }

        mustuse static bool IsKeyUp(Key key)
        {
            return s_input->IsKeyUpImpl(key);
        }

        mustuse static bool IsKeyJustPressed(Key key)
        {
            return s_input->IsKeyJustPressedImpl(key);
        }

        mustuse static f32 GetAxis(Key positive, Key negative)
        {
            return static_cast<f32>(s_input->IsKeyDownImpl(positive)) -
                   static_cast<f32>(s_input->IsKeyDownImpl(negative));
        }

        mustuse static glm::vec2 GetVector(Key x_positive, Key x_negative, Key y_positive, Key y_negative)
        {
            return {
                GetAxis(x_positive, x_negative),
                GetAxis(y_positive, y_negative),
            };
        }

        static void SetMousePosition(u32 x, u32 y)
        {
            s_input->SetMousePositionImpl(x, y);
        }

    private:
        static void Flush()
        {
            s_input->FlushImpl();
        }
    };
} // namespace Fussion
