#include "APpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h> // deletable

namespace Apate {

	OpenGLContext::OpenGLContext(GLFWwindow * windowHande)
		: m_WindowHandle(windowHande)
	{
		AP_CORE_ASSERT(windowHande, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AP_CORE_ASSERT(status, "Failed to initialize Glad!");

		AP_CORE_INFO("OpenGL Info:");
		AP_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		AP_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		AP_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
