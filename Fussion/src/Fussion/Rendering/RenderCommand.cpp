#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGlRendererApi.h"

namespace Fussion
{
    RendererAPI *RenderCommand::s_api = new OpenGLRendererAPI();
}