#include "pch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Voxel {

Application::Application() {
    VOXEL_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });
}

Application::~Application() {}

void Application::Run() {
    while (m_Running) {
        glClearColor(1, 0, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (Layer* layer : m_LayerStack) {
            layer->OnUpdate();
        }

        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return OnWindowClose(e); });

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled) {
            break;
        }
    }
}

void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* layer) {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    m_Running = false;
    return true;
}

}