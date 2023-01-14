target_sources(${ENGINE_NAME}
        WindowGLFW.cpp
        )

if (${RENDER_API} EQUAL "OpenGL")
    message("Using OpenGL")
    target_sources(${ENGINE_NAME}
            OpenGL/IndexBufferImpl.cpp
            OpenGL/OpenGLShader.cpp
            OpenGL/OpenGLTexture.cpp
            OpenGL/VertexBufferImpl.cpp
            OpenGL/VertexArrayImpl.cpp
            )
endif ()