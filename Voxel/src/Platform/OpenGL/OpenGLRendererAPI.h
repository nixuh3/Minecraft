#pragma once

#include "Voxel/Renderer/RendererAPI.h"

namespace Voxel {

class OpenGLRendererAPI : public RendererAPI {
  public:
    void Init() override;
    void SetClearColor(const glm::vec4& color) override;
    void Clear() override;

    void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
};

}
