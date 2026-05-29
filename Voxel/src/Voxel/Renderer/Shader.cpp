#include "pch.h"
#include "Shader.h"
#include "Voxel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Voxel {

Shader* Shader::Create(std::string_view vertSrc, std::string_view fragSrc) {
    switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            VOXEL_CORE_ASSERT(false, "RendererAPI::None is not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLShader(vertSrc, fragSrc);
    }

    VOXEL_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}
