#pragma once

#include <string_view>
#include <cstdint>

namespace Voxel {

class Shader {
  public:
    Shader(std::string_view vertSrc, std::string_view fragSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;

  private:
    uint32_t m_RendererID;
};

}