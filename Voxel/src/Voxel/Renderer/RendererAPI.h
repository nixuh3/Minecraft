#pragma once

#include "VertexArray.h"
#include <glm/glm.hpp>

namespace Voxel {

class RendererAPI {
  public:
    enum class API {
        None,
        OpenGL,
    };
    virtual ~RendererAPI() = default;

    virtual void SetClearColor(const glm::vec4& color) = 0;
    virtual void Clear() = 0;

    virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

    static API GetAPI() { return s_API; };
    static Scope<RendererAPI> Create();

  private:
    inline static API s_API = API::OpenGL;
};

}
