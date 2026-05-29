#pragma once

#include "Voxel/Renderer/Shader.h"
#include <cstdint>
#include <glm/glm.hpp>

namespace Voxel {

class OpenGLShader : public Shader {
  public:
    OpenGLShader(std::string_view vertSrc, std::string_view fragSrc);
    ~OpenGLShader();

    void Bind() const override;
    void Unbind() const override;

    void UploadUniformInt(std::string_view name, int value);

    void UploadUniformFloat(std::string_view name, float value);
    void UploadUniformFloat2(std::string_view name, const glm::vec2& value);
    void UploadUniformFloat3(std::string_view name, const glm::vec3& value);
    void UploadUniformFloat4(std::string_view name, const glm::vec4& value);

    void UploadUniformMat3(std::string_view name, const glm::mat3& matrix);
    void UploadUniformMat4(std::string_view name, const glm::mat4& matrix);

  private:
    uint32_t m_RendererID;
};

}
