#pragma once

#ifdef VOXEL_PLATFORM_WINDOWS
    #ifdef VOXEL_BUILD_DLL
        #define VOXEL_API __declspec(dllexport)
    #else
        #define VOXEL_API __declspec(dllimport)
    #endif
#else
    #error Voxel only supports Windows
#endif