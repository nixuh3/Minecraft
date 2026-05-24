#pragma once

#include <string_view>
#include <cstdint>
#include <glm/glm.hpp>

namespace Voxel {

class Shader {
  public:
    Shader(std::string_view vertSrc, std::string_view fragSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void UploadUniformMat4(std::string_view name, const glm::mat4& matrix);

  private:
    uint32_t m_RendererID;
};

}
