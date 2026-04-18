#pragma once

#include "Voxel/Core.h"
#include "Voxel/Events/Event.h"

namespace Voxel {

class VOXEL_API Application {
  public:
    Application();
    virtual ~Application();

    void Run();
};

Application* CreateApplication();

}
