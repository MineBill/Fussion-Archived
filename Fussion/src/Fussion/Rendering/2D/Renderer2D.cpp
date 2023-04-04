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
    constexpr u32 MaxTextureSlots = 32;

    struct Vertex {
        glm::vec3 Position{};
        glm::vec4 Color{};
        glm::vec2 TextureCoords{};
        f32 TextureIndex{0.0f};
    };

    struct RendererData {
        Ref<Texture> WhiteTexture{};
        Ref<VertexArray> QuadVertexArray{};
        Ref<VertexBuffer> QuadVertexBuffer{};
        Ref<Shader> TextureShader{};

        u32 IndexBufferCount{0};
        Vertex *VertexBufferDataBase{nullptr};
        Vertex *VertexBufferDataPtr{nullptr};

        u32 CurrentTextureIndex{1};
        // @Note Slot 0 will be used as a 'color' texture
        std::array<Ref<Texture>, MaxTextureSlots> TextureSlots{};

        DrawStats Stats;
    };

    static RendererData s_data;

    void init()
    {
        u8 pixels[3] = {0xff, 0xff, 0xff};
        s_data.WhiteTexture = Texture::from_pixels(pixels, 1, 1, 3);
        s_data.TextureSlots[0] = s_data.WhiteTexture;

        s_data.TextureShader = Shader::LoadFromFile("Resources/Shaders/Texture.glsl");

        i32 textures[MaxTextureSlots];
        for (u32 i = 0; i < MaxTextureSlots; i++)
            textures[i] = static_cast<i32>(i);

        s_data.TextureShader->set_array("u_Textures", textures, MaxTextureSlots);

        s_data.QuadVertexArray = VertexArray::Create();
        s_data.QuadVertexArray->bind();

        Fussion::AttributeLayout layout = {
            {Fussion::VertexElementType::Float3, "a_Position"},
            {Fussion::VertexElementType::Float4, "a_Color"},
            {Fussion::VertexElementType::Float2, "a_TextureCoords"},
            {Fussion::VertexElementType::Float, "a_TextureIndex"},
        };

        s_data.QuadVertexBuffer = VertexBuffer::WithSize(MaxVertices * sizeof(Vertex));
        s_data.QuadVertexBuffer->set_layout(layout);
        s_data.VertexBufferDataBase = new Vertex[MaxVertices];
        s_data.VertexBufferDataPtr = s_data.VertexBufferDataBase;

        u32 *indices = new u32[MaxIndices];

        u32 offset = 0;
        for (u32 i = 0u; i < MaxIndices; i += 6) {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        auto ib = IndexBuffer::FromSpan({indices, MaxIndices});
        s_data.QuadVertexArray->set_index_buffer(ib);
        delete[] indices;

        s_data.QuadVertexArray->add_vertex_buffer(s_data.QuadVertexBuffer);
    }

    void shutdown()
    {
        delete[] s_data.VertexBufferDataBase;
    }

    void begin_scene(const Camera2D &camera, const glm::mat4 &transform)
    {
        s_data.TextureShader->bind();
        s_data.TextureShader->set_uniform("u_ViewProjection", camera.projection() * glm::inverse(transform));

        start_batch();
    }

    void end_scene()
    {
        flush();
    }

    void flush()
    {
        FSN_PROFILE_FUNCTION();
        for (u32 i = 0; i < s_data.CurrentTextureIndex; i++) {
            s_data.TextureSlots[i]->bind(i);
        }
        auto size = reinterpret_cast<uint8_t *>(s_data.VertexBufferDataPtr) -
                    reinterpret_cast<uint8_t *>(s_data.VertexBufferDataBase);
        s_data.QuadVertexBuffer->update_sub_data(0, s_data.VertexBufferDataBase, static_cast<i32>(size));

        RenderCommand::draw_indexed(s_data.QuadVertexArray, s_data.IndexBufferCount);
    }

    void start_batch()
    {
        s_data.IndexBufferCount = 0;
        s_data.VertexBufferDataPtr = s_data.VertexBufferDataBase;
        s_data.CurrentTextureIndex = 1;

        s_data.Stats.draw_calls++;
    }

    void draw_quad(const Ref<Texture> &texture, const DrawQuadParams &params)
    {
        FSN_PROFILE_FUNCTION();

        if (s_data.IndexBufferCount >= MaxIndices) {
            end_scene();
            start_batch();
        }

        // Check if texture is already used
        f32 textureIndex = 0.0f;
        for (u32 i = 1; i < s_data.CurrentTextureIndex; i++) {
            if (s_data.TextureSlots[i]->renderer_handle() == texture->renderer_handle()) {
                textureIndex = static_cast<f32>(i);
            }
        }

        if (textureIndex == 0.0f) {
            if (s_data.CurrentTextureIndex >= MaxTextureSlots) {
                FSN_CORE_ERR("Cannot use more to_texture slots. Max is: {}", MaxTextureSlots);
            } else {
                s_data.TextureSlots[s_data.CurrentTextureIndex] = texture;
                textureIndex = static_cast<f32>(s_data.CurrentTextureIndex);
                s_data.CurrentTextureIndex++;
            }
        }

        auto trans = glm::translate(glm::mat4(1.0f), params.position) * params.parent_transform;
        auto rotationMatrix = glm::rotate(trans, params.rotation, {0, 0, 1});

        s_data.VertexBufferDataPtr->Position = rotationMatrix * glm::vec4{0, 0, 0, 1};
        s_data.VertexBufferDataPtr->Color = params.tint_color;
        s_data.VertexBufferDataPtr->TextureCoords = {0, 0};
        s_data.VertexBufferDataPtr->TextureIndex = textureIndex;
        s_data.VertexBufferDataPtr++;

        s_data.VertexBufferDataPtr->Position =
            rotationMatrix * glm::vec4(glm::vec3(1.0f, 0.0f, 0.0f) * params.scale, 1.0f);
        s_data.VertexBufferDataPtr->Color = params.tint_color;
        s_data.VertexBufferDataPtr->TextureCoords = glm::vec2{1, 0} * params.uv_scale;
        s_data.VertexBufferDataPtr->TextureIndex = textureIndex;
        s_data.VertexBufferDataPtr++;

        s_data.VertexBufferDataPtr->Position =
            rotationMatrix * glm::vec4(glm::vec3(1.0f, 1.0f, 0.0f) * params.scale, 1.0f);
        s_data.VertexBufferDataPtr->Color = params.tint_color;
        s_data.VertexBufferDataPtr->TextureCoords = glm::vec2{1, 1} * params.uv_scale;
        s_data.VertexBufferDataPtr->TextureIndex = textureIndex;
        s_data.VertexBufferDataPtr++;

        s_data.VertexBufferDataPtr->Position =
            rotationMatrix * glm::vec4(glm::vec3(0.0f, 1.0f, 0.0f) * params.scale, 1.0f);
        s_data.VertexBufferDataPtr->Color = params.tint_color;
        s_data.VertexBufferDataPtr->TextureCoords = glm::vec2{0, 1} * params.uv_scale;
        s_data.VertexBufferDataPtr->TextureIndex = textureIndex;
        s_data.VertexBufferDataPtr++;

        s_data.IndexBufferCount += 6;

        s_data.Stats.quad_count++;
    }

    void reset_stats()
    {
        s_data.Stats = {};
    }

    DrawStats draw_stats()
    {
        return s_data.Stats;
    }
} // namespace Fussion::Renderer2D
