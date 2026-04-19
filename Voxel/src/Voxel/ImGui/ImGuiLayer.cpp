#include "pch.h"
#include "ImGuiLayer.h"
#include "Voxel/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include <backends/imgui_impl_glfw.h>

// temp
#include <GLFW/glfw3.h>

namespace Voxel {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // optional
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;    // if using docking

    // If you want ImGui to hook GLFW callbacks automatically:
    // ImGui_ImplGlfw_InitForOpenGL(window, true);

    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

    ImGui_ImplGlfw_InitForOpenGL(window, false);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::OnUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& event) {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseButtonPressedEvent>(
        [this](MouseButtonPressedEvent& e) { return OnMouseButtonPressedEvent(e); });
    dispatcher.Dispatch<MouseButtonReleasedEvent>(
        [this](MouseButtonReleasedEvent& e) { return OnMouseButtonReleasedEvent(e); });
    dispatcher.Dispatch<MouseMovedEvent>(
        [this](MouseMovedEvent& e) { return OnMouseMovedEvent(e); });
    dispatcher.Dispatch<MouseScrolledEvent>(
        [this](MouseScrolledEvent& e) { return OnMouseScrolledEvent(e); });
    dispatcher.Dispatch<KeyPressedEvent>(
        [this](KeyPressedEvent& e) { return OnKeyPressedEvent(e); });
    dispatcher.Dispatch<KeyReleasedEvent>(
        [this](KeyReleasedEvent& e) { return OnKeyReleasedEvent(e); });
    dispatcher.Dispatch<KeyTypedEvent>([this](KeyTypedEvent& e) { return OnKeyTypedEvent(e); });
    dispatcher.Dispatch<WindowResizeEvent>(
        [this](WindowResizeEvent& e) { return OnWindowResizeEvent(e); });
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(e.GetMouseButton(), true);

    return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(e.GetMouseButton(), false);

    return false;
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMousePosEvent(e.GetX(), e.GetY());

    return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());

    return false;
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    // ImGuiKey key = MyKeyCodeToImGuiKey(e.GetKeyCode());
    // io.AddKeyEvent(key, true);
    return false;
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    // ImGuiKey key = MyKeyCodeToImGuiKey(e.GetKeyCode());
    // io.AddKeyEvent(key, false);
    return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    unsigned int keycode = e.GetKeyCode();
    if (keycode > 0 && keycode < 0x10000) {
        io.AddInputCharacter(keycode);
    }
    return false;
}

bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    glViewport(0, 0, e.GetWidth(), e.GetHeight());

    return false;
}

}