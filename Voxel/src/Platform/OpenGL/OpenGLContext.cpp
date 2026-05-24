#include "pch.h"
#include "OpenGLContext.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Voxel {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
    VOXEL_CORE_ASSERT(m_WindowHandle, "WindowHandle is null!");
}

void OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGL(glfwGetProcAddress);
    VOXEL_CORE_ASSERT(status, "Failed to initialize Glad!");

    VOXEL_CORE_INFO("OpenGL Info:");
    VOXEL_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
    VOXEL_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
    VOXEL_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

}
