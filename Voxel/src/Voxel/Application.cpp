#include "pch.h"
#include "Application.h"
#include "Voxel/Input.h"
#include "Voxel/Renderer/Renderer.h"

namespace Voxel {

Application::Application() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
    VOXEL_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    // clang-format off
    float vertices[] = {
        -0.5, -0.5f, 0.0f,   0.8f, 0.2f, 0.4f, 1.0f,
        0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
        0.5f,  0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f,
       -0.5f,  0.5f, 0.0f,   0.3f, 0.8f, 0.2f, 1.0f,
    };

    uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    // clang-format on

    m_VertexArray = std::shared_ptr<VertexArray>(VertexArray::Create());
    std::shared_ptr<VertexBuffer> vertexBuffer =
        std::shared_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
    std::shared_ptr<IndexBuffer> indexBuffer = std::shared_ptr<IndexBuffer>(
        IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));

    BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4,    "a_Color" },
    };

    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);

    std::string_view vertSrc = R"(
        #version 330 core
            
        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjection;

        out vec3 v_Position;
        out vec4 v_Color;

        void main() {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

    m_Shader = std::make_shared<Shader>(vertSrc, fragSrc);
}

void Application::Run() {
    while (m_Running) {
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::Clear();

        // m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
        m_Camera.SetRotation(45.f);

        Renderer::BeginScene(m_Camera);
        Renderer::Submit(m_Shader, m_VertexArray);
        Renderer::EndScene();

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
