#include "Voxel.h"

class ExampleLayer : public Voxel::Layer {
  public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override { VOXEL_INFO("ExampleLayer::Update"); }
    void OnEvent(Voxel::Event& e) override { VOXEL_TRACE(e); }
};

class Sandbox : public Voxel::Application {
  public:
    Sandbox() {
        PushLayer(new ExampleLayer());
        PushOverlay(new Voxel::ImGuiLayer());
    }

    ~Sandbox() {}
};

Voxel::Application* Voxel::CreateApplication() { return new Sandbox(); }