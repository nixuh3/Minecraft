#pragma once

#include "Voxel/Renderer/Shader.h"
#include <cstdint>
#include <glm/glm.hpp>

namespace Voxel {

class OpenGLShader : public Shader {
  public:
    OpenGLShader(std::string_view name, std::string_view vertSrc, std::string_view fragSrc);
    OpenGLShader(std::string_view filepath);
    ~OpenGLShader();

    void Bind() const override;
    void Unbind() const override;

    std::string_view GetName() const override { return m_Name; }

    void UploadUniformInt(std::string_view name, int value);

    void UploadUniformFloat(std::string_view name, float value);
    void UploadUniformFloat2(std::string_view name, const glm::vec2& value);
    void UploadUniformFloat3(std::string_view name, const glm::vec3& value);
    void UploadUniformFloat4(std::string_view name, const glm::vec4& value);

    void UploadUniformMat3(std::string_view name, const glm::mat3& matrix);
    void UploadUniformMat4(std::string_view name, const glm::mat4& matrix);

  private:
    using GLenum = unsigned int;

    std::string ReadFile(std::string_view filepath);
    std::unordered_map<GLenum, std::string> Preprocess(std::string_view source);
    void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

    uint32_t m_RendererID;
    std::string m_Name;
};

}
