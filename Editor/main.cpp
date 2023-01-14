#include "EditorApplication.hpp"

int main()
{
    Editor::EditorApplication editor{
        Fussion::WindowProps{.width = 640, .height = 480, .title = "This is a cool window"}};
    editor.Run();
}
