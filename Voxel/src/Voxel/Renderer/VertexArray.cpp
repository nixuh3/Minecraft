#include "pch.h"
#include "VertexArray.h"
#include "Voxel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Voxel {

VertexArray* VertexArray::Create() {
    switch (Renderer::GetAPI()) {
        case RendererAPI::None:
            VOXEL_CORE_ASSERT(false, "RendererAPI::None is not supported!");
            return nullptr;
        case RendererAPI::OpenGL: return new OpenGLVertexArray();
    }

    VOXEL_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}