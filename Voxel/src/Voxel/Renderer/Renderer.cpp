#include "pch.h"
#include "Renderer.h"
#include "Voxel/Renderer/OrthographicCamera.h"

namespace Voxel {

void Renderer::BeginScene(OrthographicCamera& camera) {
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(
    const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

}
