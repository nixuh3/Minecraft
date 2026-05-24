#include "Voxel.h"

#include <imgui.h>

class ExampleLayer : public Voxel::Layer {
  public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {}

    void OnImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!");
        ImGui::End();
    }

    void OnEvent(Voxel::Event& e) override { // VOXEL_TRACE(e);
    }
};

class Sandbox : public Voxel::Application {
  public:
    Sandbox() { PushLayer(new ExampleLayer()); }

    ~Sandbox() {}
};

Voxel::Application* Voxel::CreateApplication() { return new Sandbox(); }
