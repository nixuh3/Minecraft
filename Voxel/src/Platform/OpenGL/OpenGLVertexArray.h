#pragma once

#include "Voxel/Renderer/VertexArray.h"
#include <vector>
#include <cstdint>

namespace Voxel {

class OpenGLVertexArray : public VertexArray {
  public:
    OpenGLVertexArray();
    ~OpenGLVertexArray();

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
    void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

    const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override {
        return m_VertexBuffers;
    }
    const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

  private:
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;

    uint32_t m_RendererID;
};

}
