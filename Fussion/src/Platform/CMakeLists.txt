target_sources(
        ${ENGINE_NAME}
        PRIVATE
        WindowGLFW.h
        WindowGLFW.cpp
)

if (${RENDER_API} STREQUAL "OpenGL")
    message("Using OpenGL")
    target_sources(
            ${ENGINE_NAME}
            PRIVATE
            OpenGL/IndexBufferImpl.cpp
            OpenGL/OpenGLShader.cpp
            OpenGL/OpenGLTexture.cpp
            OpenGL/VertexBufferImpl.cpp
            OpenGL/VertexArrayImpl.cpp
            OpenGL/OpenGLRenderContext.h
            OpenGL/OpenGLRenderContext.cpp
    )
endif ()