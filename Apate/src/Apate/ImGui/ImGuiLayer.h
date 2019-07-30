#pragma once

#include "Apate/Layer.h"

#include "Apate/Events/ApplicationEvent.h"
#include "Apate/Events/KeyEvent.h"
#include "Apate/Events/MouseEvent.h"

namespace Apate {

	class APATE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
