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
		if (Apate::Input::IsKeyPressed(AP_KEY_TAB))
			AP_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Apate::Event& event) override
	{
		if (event.GetEventType() == Apate::EventType::KeyPressed)
		{
			Apate::KeyPressedEvent& e = (Apate::KeyPressedEvent&)event;
			if (e.GetKeyCode() == AP_KEY_TAB)
				AP_TRACE("Tab key is pressed (event)!");
			AP_TRACE("{0}", (char)e.GetKeyCode());
		}
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
