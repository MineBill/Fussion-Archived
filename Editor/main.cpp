#include "EditorApplication.hpp"
#include <Fussion/Debug/Profiling.h>

int main()
{
    Editor::EditorApplication editor{
        Fussion::WindowProps{.width = 1280, .height = 720, .title = "Fussion Editor", .dark_mode = true}};
    editor.run();
}
