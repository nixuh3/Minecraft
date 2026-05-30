#include "pch.h"
#include "Shader.h"
#include "Voxel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Voxel {

Ref<Shader> Shader::Create(std::string_view filepath) {
    switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            VOXEL_CORE_ASSERT(false, "RendererAPI::None is not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filepath);
    }

    VOXEL_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Ref<Shader> Shader::Create(
    std::string_view name, std::string_view vertSrc, std::string_view fragSrc) {
    switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            VOXEL_CORE_ASSERT(false, "RendererAPI::None is not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertSrc, fragSrc);
    }

    VOXEL_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

void ShaderLibrary::Add(std::string_view name, const Ref<Shader>& shader) {
    VOXEL_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exist");
    m_Shaders[name] = shader;
}

void ShaderLibrary::Add(const Ref<Shader>& shader) {
    auto name = shader->GetName();
    Add(name, shader);
}

Ref<Shader> ShaderLibrary::Load(std::string_view name, std::string_view filepath) {
    auto shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

Ref<Shader> ShaderLibrary::Load(std::string_view filepath) {
    auto shader = Shader::Create(filepath);
    Add(shader);
    return shader;
}

Ref<Shader> ShaderLibrary::Get(std::string_view name) {
    VOXEL_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found");
    return m_Shaders[name];
}

}
