#pragma once

#include "Voxel/Core.h"
#include "Voxel/Window.h"
#include "Voxel/LayerStack.h"
#include "Voxel/Events/ApplicationEvent.h"
#include "Voxel/ImGui/ImGuiLayer.h"
#include "Voxel/Renderer/Shader.h"
#include "Voxel/Renderer/Buffer.h"
#include "Voxel/Renderer/VertexArray.h"

#include <memory>

namespace Voxel {

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

    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexArray> m_VertexArray;

    inline static Application* s_Instance = nullptr;
};

Application* CreateApplication();

}
