#pragma once

#include "Voxel/Window.h"
#include "Voxel/LayerStack.h"
#include "Voxel/ImGui/ImGuiLayer.h"

#include <memory>

namespace Voxel {

class WindowCloseEvent;

class Application {
  public:
    Application();
    virtual ~Application() = default;

    void Run();
    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    static Application& Get() { return *s_Instance; }
    Window& GetWindow() const { return *m_Window; }

  private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    bool m_Running = true;
    LayerStack m_LayerStack;

    float m_LastFrameTime = 0.0f;

    inline static Application* s_Instance = nullptr;
};

Application* CreateApplication();

}
