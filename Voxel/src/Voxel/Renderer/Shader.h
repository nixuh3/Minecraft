#pragma once

#include <string_view>
#include <unordered_map>

namespace Voxel {

class Shader {
  public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual std::string_view GetName() const = 0;

    static Ref<Shader> Create(std::string_view filepath);
    static Ref<Shader> Create(
        std::string_view name, std::string_view vertSrc, std::string_view fragSrc);
};

class ShaderLibrary {
  public:
    void Add(std::string_view name, const Ref<Shader>& shader);
    void Add(const Ref<Shader>& shader);
    Ref<Shader> Load(std::string_view name, std::string_view filepath);
    Ref<Shader> Load(std::string_view filepath);

    Ref<Shader> Get(std::string_view name);

  private:
    std::unordered_map<std::string_view, Ref<Shader>> m_Shaders;
};

}
