#include "Apate.h"

#include "imgui/imgui.h"

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
			-0.75f, -0.75f, 0.0f,
			+0.75f, -0.75f, 0.0f,
			+0.75f, +0.75f, 0.0f,
			-0.75f, +0.75f, 0.0f,
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

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
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

		m_Shader.reset(new Apate::Shader(vertexSrc, FragmentSrc));

		std::string BlueShaderVertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjection;

				out vec3 v_Position;

				void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
				}
		)";

		std::string BlueShaderFragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;

				in vec3 v_Position;

				void main()
				{
					color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
				}
		)";

		m_BlueShader.reset(new Apate::Shader(BlueShaderVertexSrc, BlueShaderFragmentSrc));
	}

	void OnUpdate(Apate::Timestep ts) override
	{
		AP_TRACE("Delta time: {0}s ({1}ms)", ts.GetSecond(), ts.GetMillisecond());

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

		Apate::Renderer::Submit(m_BlueShader, m_SquareVA);
		Apate::Renderer::Submit(m_Shader, m_VertexArray);

		Apate::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Apate::Event& event) override
	{
	}
private:
	std::shared_ptr<Apate::Shader> m_Shader;
	std::shared_ptr<Apate::VertexArray> m_VertexArray;

	std::shared_ptr<Apate::Shader> m_BlueShader;
	std::shared_ptr<Apate::VertexArray> m_SquareVA;

	Apate::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
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
