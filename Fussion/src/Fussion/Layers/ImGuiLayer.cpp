#include "ImGuiLayer.hpp"
#include "Fussion/Application.hpp"
#include "Fussion/Events/ApplicationEvents.hpp"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>

using namespace fussion;

void ImGuiLayer::OnLoad()
{
    std::cout << "ImGuiLayer::OnLoad\n";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(Application::GetInstance().GetWindow().Raw()), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void ImGuiLayer::OnUpdate(f32 elapsed)
{
    (void)elapsed;
}

void ImGuiLayer::OnEvent(const Ref<Event> &)
{
}

void ImGuiLayer::BeginFrame(f32)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::EndFrame()
{
    ImGui::Render();
//    ImGui::UpdatePlatformWindows();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    auto& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}
