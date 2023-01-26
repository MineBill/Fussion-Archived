#include "ImGuiLayer.h"
#include "Fussion/Core/Application.h"
#include "Fussion/Events/ApplicationEvents.h"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>

using namespace Fussion;

void ImGuiLayer::on_load()
{
    std::cout << "ImGuiLayer::on_load\n";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(Application::get().window().raw_ptr()), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    auto &style = ImGui::GetStyle();
    style.WindowRounding = 4;
    style.ChildRounding = 4;
    style.FrameRounding = 4;
    style.TabRounding = 4;
    style.GrabRounding = 4;
    style.ScrollbarRounding = 4;
    style.PopupRounding = 4;
    style.FramePadding = {3, 3};
}

void ImGuiLayer::on_update(f32 elapsed)
{
    (void)elapsed;
}

bool ImGuiLayer::on_event(Event &)
{
    return false;
}

void ImGuiLayer::begin_frame(f32)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::end_frame()
{
    ImGui::Render();
    //    ImGui::UpdatePlatformWindows();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    auto &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}
