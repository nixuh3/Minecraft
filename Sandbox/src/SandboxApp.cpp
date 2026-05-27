#include "ExampleLayer.h"
#include <Voxel/EntryPoint.h>

class Sandbox : public Voxel::Application {
  public:
    Sandbox() { PushLayer(new ExampleLayer()); }

    ~Sandbox() {}
};

Voxel::Application* Voxel::CreateApplication() { return new Sandbox(); }
