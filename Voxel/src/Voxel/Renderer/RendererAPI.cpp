#include "pch.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Voxel {

Scope<RendererAPI> RendererAPI::Create() {
    switch (s_API) {
        case RendererAPI::API::None:
            VOXEL_CORE_ASSERT(false, "RendererAPI::None is not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
    }

    VOXEL_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}
