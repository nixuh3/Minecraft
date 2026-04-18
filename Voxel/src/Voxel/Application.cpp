#include "pch.h"
#include "Application.h"

#include "Voxel/Events/ApplicationEvent.h"
#include "Voxel/Log.h"

namespace Voxel {

Application::Application() {}

Application::~Application() {}

void Application::Run() {
    WindowResizeEvent e(500, 500);
    VOXEL_CORE_WARN(e);

    while (true) {
    }
}

}