#pragma once

#include "Voxel/Core/Timestep.h"
#include <string>

namespace Voxel {

class Event;

class Layer {
  public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate(Timestep ts) {}
    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event& event) {}

    const std::string& GetName() const { return m_DebugName; }

  protected:
    const std::string m_DebugName;
};

}
