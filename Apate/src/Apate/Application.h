#pragma once

#include "Core.h"

#include "Window.h"
#include "Apate/LayerStack.h"
#include "Apate/Events/Event.h"
#include "Apate/Events/ApplicationEvent.h"

#include "Apate/Core/Timestep.h"

#include "Apate/ImGui/ImGuiLayer.h"

namespace Apate {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
