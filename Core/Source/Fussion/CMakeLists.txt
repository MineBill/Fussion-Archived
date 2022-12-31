target_sources(
        ${ENGINE_NAME}
        PRIVATE

        Types.hpp
        Application.hpp
        Application.cpp
        Window.hpp

        Input/Keys.hpp
        Events/Event.hpp
        Events/MouseEvents.hpp
        Events/KeyboardEvents.hpp
        Events/ApplicationEvents.hpp
)
