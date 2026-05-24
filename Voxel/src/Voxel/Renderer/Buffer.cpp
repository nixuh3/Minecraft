#include "pch.h"
#include "Voxel/Renderer/Buffer.h"
#include "Voxel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Voxel {

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
    switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            VOXEL_CORE_ASSERT(false, "RendererAPI::None is not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
    }

    VOXEL_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
    switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            VOXEL_CORE_ASSERT(false, "RendererAPI::None is not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
    }

    VOXEL_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}
