#pragma once

#include "Voxel/Core.h"
#include "Voxel/Window.h"
#include "Events/ApplicationEvent.h"
#include <memory>

namespace Voxel {

class VOXEL_API Application {
  public:
    Application();
    virtual ~Application();

    void Run();
    void OnEvent(Event& e);

  private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
};

Application* CreateApplication();

}
