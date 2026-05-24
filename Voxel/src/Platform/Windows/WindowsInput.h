#pragma once

#include "Voxel/Input.h"

namespace Voxel {

class WindowsInput : public Input {
  protected:
    bool IsKeyPressedImpl(int keycode) override;
    bool IsMouseButtonPressedImpl(int button) override;
    std::pair<float, float> GetMousePositionImpl() override;
    float GetMouseXImpl() override;
    float GetMouseYImpl() override;
};

}
