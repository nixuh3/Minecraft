#pragma once

#include "Voxel/Window.h"
#include "Voxel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Voxel {

class WindowsWindow : public Window {
  public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    void OnUpdate() override;

    unsigned int GetWidth() const override { return m_Data.Width; }
    unsigned int GetHeight() const override { return m_Data.Height; }

    // Window attributes
    void SetEventCallback(const EventCallbackFn& callback) override {
        m_Data.EventCallback = callback;
    }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    void* GetNativeWindow() const { return m_Window; }

  private:
    void Init(const WindowProps& props);
    void Shutdown();

    GLFWwindow* m_Window;
    GraphicsContext* m_Context;

    struct WindowData {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;

        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};

}
