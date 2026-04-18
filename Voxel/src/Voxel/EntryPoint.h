#pragma once

#ifdef VOXEL_PLATFORM_WINDOWS

    #include "Voxel/Application.h"

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