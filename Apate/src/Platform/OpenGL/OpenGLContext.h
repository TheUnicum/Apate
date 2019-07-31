#pragma once

#include "Apate/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Apate {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHande);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}
