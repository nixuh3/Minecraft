#pragma once

#include "Voxel/Renderer/RenderCommand.h"
#include "Voxel/Renderer/Shader.h"

namespace Voxel {

class OrthographicCamera;

class Renderer {
  public:
    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,
        const glm::mat4& transform = glm::mat4(1.0f));

    static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

  private:
    struct SceneData {
        glm::mat4 ViewProjectionMatrix;
    };

    inline static Scope<SceneData> s_SceneData = CreateScope<SceneData>();
};

}
