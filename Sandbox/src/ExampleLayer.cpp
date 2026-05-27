#include "ExampleLayer.h"
#include <glm/gtc/matrix_transform.hpp>

ExampleLayer::ExampleLayer()
    : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
    // clang-format off
    float vertices[] = {
        // -1.0f, -1.0f, 0.0f,   0.8f, 0.2f, 0.4f, 1.0f,
        // -0.5f, -1.0f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
        // -1.0f, -0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f,
        
        -0.5f, -0.5f, 0.0f,   0.8f, 0.2f, 0.4f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
         0.5f,  0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f,
        -0.5f,  0.5f, 0.0f,   0.3f, 0.8f, 0.2f, 1.0f,
    };

    uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
    // clang-format on

    m_VertexArray = std::shared_ptr<Voxel::VertexArray>(Voxel::VertexArray::Create());
    std::shared_ptr<Voxel::VertexBuffer> vertexBuffer = std::shared_ptr<Voxel::VertexBuffer>(
        Voxel::VertexBuffer::Create(vertices, sizeof(vertices)));
    Voxel::BufferLayout layout = {
        { Voxel::ShaderDataType::Float3, "a_Position" },
        { Voxel::ShaderDataType::Float4,    "a_Color" },
    };
    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    std::shared_ptr<Voxel::IndexBuffer> indexBuffer = std::shared_ptr<Voxel::IndexBuffer>(
        Voxel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    // square
    // clang-format off
    float squareVertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
    // clang-format on

    m_SquareVA = std::shared_ptr<Voxel::VertexArray>(Voxel::VertexArray::Create());
    std::shared_ptr<Voxel::VertexBuffer> squareVB = std::shared_ptr<Voxel::VertexBuffer>(
        Voxel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({
        { Voxel::ShaderDataType::Float3, "a_Position" }
    });
    m_SquareVA->AddVertexBuffer(squareVB);

    std::shared_ptr<Voxel::IndexBuffer> squareIB = std::shared_ptr<Voxel::IndexBuffer>(
        Voxel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIB);

    std::string_view vertSrc = R"(
        #version 330 core
            
        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec4 v_Color;

        void main() {
            v_Color = a_Color;
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
        }
    )";

    std::string_view fragSrc = R"(
        #version 330 core
            
        layout(location = 0) out vec4 color;

        in vec4 v_Color;

        void main() {
            color = v_Color;
        }
    )";

    m_Shader = std::make_shared<Voxel::Shader>(vertSrc, fragSrc);

    std::string_view squareVert = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;

        void main() {
            v_Position = a_Position;
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
        }
    )";

    std::string_view squareFrag = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main() {
            color = vec4(0.2, 0.2, 0.2, 1.0);
        }
    )";

    m_SquareShader = std::make_shared<Voxel::Shader>(squareVert, squareFrag);
}

void ExampleLayer::OnUpdate(Voxel::Timestep ts) {
    if (Voxel::Input::IsKeyPressed(VOXEL_KEY_LEFT)) {
        m_CameraPosition.x -= m_CameraMoveSpeed * ts.GetSeconds();
    } else if (Voxel::Input::IsKeyPressed(VOXEL_KEY_RIGHT)) {
        m_CameraPosition.x += m_CameraMoveSpeed * ts.GetSeconds();
    }
    if (Voxel::Input::IsKeyPressed(VOXEL_KEY_DOWN)) {
        m_CameraPosition.y -= m_CameraMoveSpeed * ts.GetSeconds();
    } else if (Voxel::Input::IsKeyPressed(VOXEL_KEY_UP)) {
        m_CameraPosition.y += m_CameraMoveSpeed * ts.GetSeconds();
    }
    if (Voxel::Input::IsKeyPressed(VOXEL_KEY_A)) {
        m_CameraRotation += m_CameraRotationSpeed * ts.GetSeconds();
    } else if (Voxel::Input::IsKeyPressed(VOXEL_KEY_D)) {
        m_CameraRotation -= m_CameraRotationSpeed * ts.GetSeconds();
    }

    Voxel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Voxel::RenderCommand::Clear();

    m_Camera.SetPosition(m_CameraPosition);
    m_Camera.SetRotation(m_CameraRotation);

    Voxel::Renderer::BeginScene(m_Camera);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
            Voxel::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
        }
    }

    Voxel::Renderer::Submit(m_Shader, m_VertexArray);
    Voxel::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender() {}

void ExampleLayer::OnEvent(Voxel::Event& e) {}
