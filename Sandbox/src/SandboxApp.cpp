#include "Voxel.h"

class ExampleLayer : public Voxel::Layer {
  public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        if (Voxel::Input::IsKeyPressed(VOXEL_KEY_TAB)) {
            VOXEL_TRACE("Tab key pressed");
        }
    }

    void OnEvent(Voxel::Event& e) override { // VOXEL_TRACE(e);
    }
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