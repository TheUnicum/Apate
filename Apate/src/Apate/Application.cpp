#include "Application.h"

#include "Apate/Events/ApplicationEvent.h"
#include "Apate/Events/KeyEvent.h"
#include "Apate/Events/MouseEvent.h"
#include "Apate/Log.h"

namespace Apate {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent winRes(1280, 720);
		if (winRes.IsInCategory(EventCategoryApplication))
			AP_TRACE(winRes);

		KeyPressedEvent keyPres(345, 34);
		if (keyPres.IsInCategory(EventCategoryInput))
			AP_TRACE(keyPres);

		MouseButtonPressedEvent mousePres(77);
		if (mousePres.IsInCategory(EventCategoryMouse))
			AP_TRACE(mousePres);

		while (true);
	}

}
