#include "pch.h"
#include "Application.h"
#include "Voxel/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Voxel {

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4: return GL_FLOAT;
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4: return GL_INT;
        case ShaderDataType::Bool: return GL_BOOL;
    }

    VOXEL_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

Application::Application() {
    VOXEL_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    // clang-format off
    float vertices[] = {
        -0.5, -0.5f, 0.0f,   0.8f, 0.2f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
        0.0f,  0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f,
    };

    uint32_t indices[] = {
        0, 1, 2,
    };
    // clang-format on

    m_VertexBuffer =
        std::unique_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
    m_IndexBuffer = std::unique_ptr<IndexBuffer>(
        IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));

    {
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4,    "a_Color" },
        };

        m_VertexBuffer->SetLayout(layout);
    }

    const auto& layout = m_VertexBuffer->GetLayout();
    for (uint32_t index = 0; const auto& element : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.GetComponentCount(),
            ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE,
            layout.GetStride(), (const void*)element.Offset);
        index++;
    }

    std::string_view vertSrc = R"(
		#version 330 core
			
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		out vec3 v_Position;
		out vec4 v_Color;

		void main() {
			v_Position = a_Position;
            v_Color = a_Color;
			gl_Position = vec4(a_Position, 1.0);	
		}
	)";

    std::string_view fragSrc = R"(
		#version 330 core
			
		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		in vec4 v_Color;

		void main() {
			//color = vec4(v_Position * 0.5 + 0.5, 1.0);
            color = v_Color;
		}
	)";

    m_Shader = std::make_unique<Shader>(vertSrc, fragSrc);
}

void Application::Run() {
    while (m_Running) {
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->Bind();
        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

        for (Layer* layer : m_LayerStack) {
            layer->OnUpdate();
        }

        m_ImGuiLayer->Begin();
        for (Layer* layer : m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return OnWindowClose(e); });

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled) {
            break;
        }
    }
}

void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer* layer) { m_LayerStack.PushOverlay(layer); }

bool Application::OnWindowClose(WindowCloseEvent& e) {
    m_Running = false;
    return true;
}

}