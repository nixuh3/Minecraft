#pragma once

#include "Voxel/Application.h"

#ifdef VOXEL_PLATFORM_WINDOWS

extern Voxel::Application* Voxel::CreateApplication();

int main(int argc, char** argv) {
    Voxel::Log::Init();
    VOXEL_CORE_WARN("Initalized Log");

    auto app = Voxel::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif
