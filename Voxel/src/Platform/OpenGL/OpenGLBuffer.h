#pragma once

#include "Voxel/Renderer/Buffer.h"

namespace Voxel {

class OpenGLVertexBuffer : public VertexBuffer {
  public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    ~OpenGLVertexBuffer();

    void Bind() const override;
    void Unbind() const override;

  private:
    uint32_t m_RendererID;
};

class OpenGLIndexBuffer : public IndexBuffer {
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    ~OpenGLIndexBuffer();

    void Bind() const override;
    void Unbind() const override;

     uint32_t GetCount() const { return m_Count; }

  private:
    uint32_t m_RendererID;
    uint32_t m_Count;
};

}