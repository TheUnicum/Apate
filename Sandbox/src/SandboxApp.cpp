#include "Apate.h"

class ExampleLayer : public Apate::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		AP_INFO("ExampleLayer::Update");
	}

	void OnEvent(Apate::Event& event) override
	{
		AP_TRACE("{0}", event);
	}

};

class Sandbox : public Apate::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Apate::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Apate::Application* Apate::CreateApplication()
{
	return new Sandbox();
}
