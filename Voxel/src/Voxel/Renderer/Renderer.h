#pragma once

namespace Voxel {

enum class RendererAPI {
    None,
    OpenGL,
};

class Renderer {
  public:
    static RendererAPI GetAPI() { return s_RendererAPI; }

  private:
    inline static RendererAPI s_RendererAPI = RendererAPI::OpenGL;
};

}