target_sources(
        ${ENGINE_NAME}
        PRIVATE
        WindowGLFW.h
        WindowGLFW.cpp
        GlfwInput.h
        GlfwInput.cpp
)

if (${RENDER_API} STREQUAL "OpenGL")
    message("Using OpenGL")
    target_sources(
            ${ENGINE_NAME}
            PRIVATE
            OpenGL/OpenGLShader.h
            OpenGL/OpenGLShader.cpp
            OpenGL/OpenGLTexture.cpp
            OpenGL/OpenGLVertexBuffer.h
            OpenGL/OpenGLVertexBuffer.cpp
            OpenGL/OpenGLIndexBuffer.h
            OpenGL/OpenGLIndexBuffer.cpp
            OpenGL/OpenGLVertexArray.h
            OpenGL/OpenGLVertexArray.cpp
            OpenGL/OpenGLRenderContext.h
            OpenGL/OpenGLRenderContext.cpp
            OpenGL/OpenGlRendererApi.h
            OpenGL/OpenGlRendererApi.cpp
    )
endif ()