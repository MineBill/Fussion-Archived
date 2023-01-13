#include "Editor.hpp"

int main()
{
    editor::Editor editor {fussion::WindowProps{.width = 640, .height = 480, .title = "This is a cool window"}};
    editor.Run();
}
