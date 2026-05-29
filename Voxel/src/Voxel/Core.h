#pragma once

#ifndef VOXEL_PLATFORM_WINDOWS
    #error Voxel only supports Windows!
#endif

#include <memory>

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

namespace Voxel {

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

}
