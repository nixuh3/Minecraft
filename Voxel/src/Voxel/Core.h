#pragma once

#ifdef VOXEL_PLATFORM_WINDOWS
    #ifdef VOXEL_BUILD_DLL
        #define VOXEL_API __declspec(dllexport)
    #else
        #define VOXEL_API __declspec(dllimport)
    #endif
#else
    #error Voxel only supports Windows!
#endif

#ifdef VOXEL_DEBUG
    #define VOXEL_ENABLE_ASSERTS
#endif

#ifdef VOXEL_ENABLE_ASSERTS
    #define VOXEL_ASSERT(x, ...)                                   \
        {                                                          \
            if (!(x)) {                                            \
                VOXEL_ERROR("Assertion failed: {0}", __VA_ARGS__); \
                __debugbreak();                                    \
            }                                                      \
        }
    #define VOXEL_CORE_ASSERT(x, ...)                                   \
        {                                                               \
            if (!(x)) {                                                 \
                VOXEL_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); \
                __debugbreak();                                         \
            }                                                           \
        }

#else
    #define VOXEL_ASSERT(x, ...)
    #define VOXEL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << (x))