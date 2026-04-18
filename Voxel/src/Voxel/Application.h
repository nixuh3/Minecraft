#pragma once

#include "Voxel/Core.h"
#include "Voxel/Window.h"
#include <memory>

namespace Voxel {

class VOXEL_API Application {
  public:
    Application();
    virtual ~Application();

    void Run();

  private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
};

Application* CreateApplication();

}
