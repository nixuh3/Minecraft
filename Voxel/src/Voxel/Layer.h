#pragma once

#include <string>
#include "Voxel/Events/Event.h"

namespace Voxel {

class VOXEL_API Layer {
  public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnEvent(Event& event) {}

    const std::string& GetName() const { return m_DebugName; }

  protected:
    const std::string m_DebugName;
};

}