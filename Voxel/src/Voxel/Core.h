#pragma once

#ifndef VOXEL_PLATFORM_WINDOWS
    #error Voxel only supports Windows!
#endif

#ifdef VOXEL_DEBUG
    #define VOXEL_ENABLE_ASSERTS
#endif

#ifdef VOXEL_ENABLE_ASSERTS
    #define VOXEL_ASSERT(x, ...)                                   \
        do {                                                       \
            if (!(x)) {                                            \
                VOXEL_ERROR("Assertion failed: {0}", __VA_ARGS__); \
                __debugbreak();                                    \
            }                                                      \
        } while (0)
    #define VOXEL_CORE_ASSERT(x, ...)                                   \
        do {                                                            \
            if (!(x)) {                                                 \
                VOXEL_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); \
                __debugbreak();                                         \
            }                                                           \
        } while (0)

#else
    #define VOXEL_ASSERT(x, ...)
    #define VOXEL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << (x))
