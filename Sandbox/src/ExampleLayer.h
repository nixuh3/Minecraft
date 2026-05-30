#pragma once

#include <Voxel.h>
#include <imgui.h>

class ExampleLayer : public Voxel::Layer {
  public:
    ExampleLayer();

    void OnUpdate(Voxel::Timestep ts) override;
    void OnImGuiRender() override;
    void OnEvent(Voxel::Event& e) override;

  private:
    Voxel::ShaderLibrary m_ShaderLibrary;
    Voxel::Ref<Voxel::Shader> m_Shader;
    Voxel::Ref<Voxel::VertexArray> m_VertexArray;

    Voxel::Ref<Voxel::Shader> m_FlatColorShader;
    Voxel::Ref<Voxel::VertexArray> m_SquareVA;

    Voxel::Ref<Voxel::Texture2D> m_Texture;

    Voxel::OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
