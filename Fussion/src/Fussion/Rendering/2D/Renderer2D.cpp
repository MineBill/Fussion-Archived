#include "Renderer2D.h"
#include "Fussion/Debug/Profiling.h"
#include "Fussion/Rendering/RenderCommand.h"
#include "Fussion/Rendering/Shader.h"
#include "Fussion/Rendering/VertexArray.h"
#include "glm/ext/matrix_transform.hpp"
#include <span>

namespace Fussion::Renderer2D
{
    constexpr u32 MaxQuads = 10'000;
    constexpr u32 MaxVertices = MaxQuads * 4;
    constexpr u32 MaxIndices = MaxQuads * 6;

    struct Vertex {
        glm::vec3 Position{};
        glm::vec4 Color{};
        glm::vec2 TextureCoords{};
        // f32 TextureIndex{0.0f};
    };

    struct Renderer2DStorage {
        Ref<VertexArray> QuadVertexArray{};
        Ref<VertexBuffer> QuadVertexBuffer{};
        Ref<Shader> TextureShader{};

        u32 IndexBufferCount{0};
        Vertex *VertexBufferDataBase{nullptr};
        Vertex *VertexBufferDataPtr{nullptr};
    };

    static Renderer2DStorage s_storage;

    void Init()
    {
        s_storage.TextureShader = Shader::LoadFromFile("Resources/Shaders/Texture.glsl");
        // s_storage.TextureShader->SetUniform("u_Texture", 0);

        s_storage.QuadVertexArray = VertexArray::Create();
        s_storage.QuadVertexArray->Use();

        Fussion::AttributeLayout layout = {
            {Fussion::VertexElementType::Float3, "a_Position"},
            {Fussion::VertexElementType::Float4, "a_Color"},
            {Fussion::VertexElementType::Float2, "a_TextureCoords"},
        };

        s_storage.QuadVertexBuffer = VertexBuffer::WithSize(MaxVertices * sizeof(Vertex));
        s_storage.QuadVertexBuffer->SetLayout(layout);
        s_storage.VertexBufferDataBase = new Vertex[MaxVertices];
        s_storage.VertexBufferDataPtr = s_storage.VertexBufferDataBase;

        u32 *indices = new u32[MaxIndices];

        u32 offset = 0;
        for (u32 i = 0u; i < MaxIndices; i+=6) {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        auto ib = IndexBuffer::FromSpan({indices, MaxIndices});
        s_storage.QuadVertexArray->SetIndexBuffer(ib);
        delete[] indices;

        s_storage.QuadVertexArray->AddVertexBuffer(s_storage.QuadVertexBuffer);
    }

    void Shutdown()
    {
        delete[] s_storage.VertexBufferDataBase;
    }

    void BeginScene(const Camera2D &camera)
    {
        s_storage.TextureShader->Use();
        s_storage.TextureShader->SetUniform("u_ViewProjection", camera.GetViewProjection());

        s_storage.IndexBufferCount = 0;
        s_storage.VertexBufferDataPtr = s_storage.VertexBufferDataBase;
    }

    void EndScene()
    {
        Flush();
    }

    void Flush()
    {
        FSN_PROFILE_FUNCTION();
        auto size = reinterpret_cast<uint8_t*>(s_storage.VertexBufferDataPtr) - reinterpret_cast<uint8_t*>(s_storage.VertexBufferDataBase);
        s_storage.QuadVertexBuffer->UpdateSubDataRawPtr(0, s_storage.VertexBufferDataBase, static_cast<i32>(size));

        RenderCommand::DrawIndexed(s_storage.QuadVertexArray, s_storage.IndexBufferCount);
    }

    void DrawQuad(const Ref<Texture> &texture, const glm::vec3 &position, f32 rotation, const glm::vec3 &scale,
                  const glm::vec2 &uvScale)
    {
        FSN_PROFILE_FUNCTION();
        unused texture;
        unused rotation;

        s_storage.VertexBufferDataPtr->Position = position;
        s_storage.VertexBufferDataPtr->Color = {1, 1, 1, 1};
        s_storage.VertexBufferDataPtr->TextureCoords = {0, 0};
        s_storage.VertexBufferDataPtr++;

        s_storage.VertexBufferDataPtr->Position = position + glm::vec3(1.0f, 0.0f, 0.0f) * scale;
        s_storage.VertexBufferDataPtr->Color = {1, 1, 1, 1};
        s_storage.VertexBufferDataPtr->TextureCoords = glm::vec2{1, 0} * uvScale;
        s_storage.VertexBufferDataPtr++;

        s_storage.VertexBufferDataPtr->Position = position + glm::vec3(1.0f, 1.0f, 0.0f) * scale;
        s_storage.VertexBufferDataPtr->Color = {1, 0, 0, 1};
        s_storage.VertexBufferDataPtr->TextureCoords = glm::vec2{1, 1} * uvScale;
        s_storage.VertexBufferDataPtr++;

        s_storage.VertexBufferDataPtr->Position = position + glm::vec3(0.0f, 1.0f, 0.0f) * scale;
        s_storage.VertexBufferDataPtr->Color = {1, 1, 1, 1};
        s_storage.VertexBufferDataPtr->TextureCoords = glm::vec2{0, 1} * uvScale;
        s_storage.VertexBufferDataPtr++;

        s_storage.IndexBufferCount += 6;
#if 0
        auto model = glm::scale(glm::mat4(1.0f), scale);
        model = glm::rotate(model, glm::radians(rotation), {0, 0, 1});
        model = glm::translate(model, position);

        s_storage.TextureShader->Use();
        s_storage.TextureShader->SetUniform("u_Model", model);
        s_storage.TextureShader->SetUniform("u_TintColor", glm::vec4(1.0f, 0.8f, 0.8f, 1.0f));

        texture->Use(0);
        s_storage.QuadVertexArray->Use();
        RenderCommand::DrawIndexed(s_storage.QuadVertexArray);
#endif
    }
} // namespace Fussion::Renderer2D
