#include "Voxel.h"

class Sandbox : public Voxel::Application {
  public:
    Sandbox() {}
    ~Sandbox() {}


};

Voxel::Application* Voxel::CreateApplication() {
    return new Sandbox();
}