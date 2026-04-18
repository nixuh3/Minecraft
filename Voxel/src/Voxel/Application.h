#pragma once

#include "Core.h"

namespace Voxel {

class VOXEL_API Application {
  public:
    Application();
    virtual ~Application();

    void Run();
};

Application* CreateApplication();

} // namespace Voxel
