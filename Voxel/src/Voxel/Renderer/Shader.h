#pragma once

#include <string_view>

namespace Voxel {

class Shader {
  public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static Shader* Create(std::string_view vertSrc, std::string_view fragSrc);
};

}
