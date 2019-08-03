#include "APpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Apate {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
