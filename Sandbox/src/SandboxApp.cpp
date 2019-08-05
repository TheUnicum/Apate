#include "Apate.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Apate::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6, +1.6f, -0.9f, +0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Apate::VertexArray::Create());

		float vertices[3 * (3 + 4)] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			+0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			+0.0f, +0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		std::shared_ptr<Apate::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Apate::VertexBuffer::Create(vertices, sizeof(vertices)));
		Apate::BufferLayout layout = {
			{ Apate::ShaderDataType::Float3, "a_Position"},
			{ Apate::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Apate::IndexBuffer> indexBuffer;
		indexBuffer.reset(Apate::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Apate::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			+0.5f, -0.5f, 0.0f,
			+0.5f, +0.5f, 0.0f,
			-0.5f, +0.5f, 0.0f,
		};

		std::shared_ptr<Apate::VertexBuffer> squareVB;
		squareVB.reset(Apate::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Apate::ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2 , 2, 3, 0 };
		std::shared_ptr<Apate::IndexBuffer> squareIB;
		squareIB.reset(Apate::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
				}
		)";

		std::string FragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;

				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					color = vec4(v_Position * 0.5 + 0.5, 1.0f);
					color = v_Color;
				}
		)";

		m_Shader.reset(Apate::Shader::Create(vertexSrc, FragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;

				void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
				}
		)";

		std::string flatColorShaderFragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;

				in vec3 v_Position;

				uniform vec3 u_Color;

				void main()
				{
					color = vec4(u_Color, 1.0f);
				}
		)";

		m_FlatColorShader.reset(Apate::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void OnUpdate(Apate::Timestep ts) override
	{
		if (Apate::Input::IsKeyPressed(AP_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Apate::Input::IsKeyPressed(AP_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Apate::Input::IsKeyPressed(AP_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Apate::Input::IsKeyPressed(AP_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Apate::Input::IsKeyPressed(AP_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Apate::Input::IsKeyPressed(AP_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Apate::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Apate::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Apate::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)); // calculate only one time

		std::dynamic_pointer_cast<Apate::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Apate::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int i = 0; i < 20; i++)
			{
				glm::vec3 pos(i * 0.11, y * 0.11, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Apate::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		Apate::Renderer::Submit(m_Shader, m_VertexArray);

		Apate::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Apate::Event& event) override
	{
	}
private:
	std::shared_ptr<Apate::Shader> m_Shader;
	std::shared_ptr<Apate::VertexArray> m_VertexArray;

	std::shared_ptr<Apate::Shader> m_FlatColorShader;
	std::shared_ptr<Apate::VertexArray> m_SquareVA;

	Apate::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Apate::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Apate::Application* Apate::CreateApplication()
{
	return new Sandbox();
}
