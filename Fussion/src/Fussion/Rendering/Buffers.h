#pragma once
#include <Fussion/Core/Core.h>

namespace Fussion
{
    enum class VertexElementType {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Int,
        Int2,
        Int3,
        Int4,
        Mat4,
    };

    static i32 vertex_element_type_size(VertexElementType type)
    {
        using enum VertexElementType;
        // clang-format off
        switch (type) {
        case Int:
        case Float:  return 4;
        case Int2:
        case Float2: return 4 * 2;
        case Int3:
        case Float3: return 4 * 3;
        case Int4:
        case Float4: return 4 * 4;
        case Mat4:   return 4 * 4 * 4;
        default:     return 0;
        }
        // clang-format on
    }

    static i32 vertex_element_type_count(VertexElementType type)
    {
        using enum VertexElementType;
        // clang-format off
        switch (type) {
        case Int:
        case Float:  return 1;
        case Int2:
        case Float2: return 2;
        case Int3:
        case Float3: return 3;
        case Int4:
        case Float4: return 4;
        case Mat4:   return 4 * 4;
        default:     return 0;
        }
        // clang-format on
    }

    struct Attribute {
        VertexElementType Type;
        String Name;
        i32 Size;
        i32 Count;
        i32 Offset;

        Attribute(VertexElementType type, StringView name)
            : Type(type), Name(name), Size(vertex_element_type_size(type)), Count(vertex_element_type_count(type)),
              Offset(0)
        {
        }
    };

    class AttributeLayout
    {
        std::vector<Attribute> m_attributes{};
        i32 m_stride{0};

        void calculate_offset_and_stride()
        {
            for (auto &attribute : m_attributes) {
                attribute.Offset = m_stride;
                m_stride += attribute.Size;
            }
        }

    public:
        AttributeLayout(const std::initializer_list<Attribute> &attributes) : m_attributes(attributes)
        {
            calculate_offset_and_stride();
        }

        mustuse inline i32 stride() const
        {
            return m_stride;
        }

        mustuse inline const std::vector<Attribute> &attributes() const
        {
            return m_attributes;
        }
    };

    class VertexBuffer
    {
    public:
        static Ref<VertexBuffer> Create(std::initializer_list<f32> vertices);
        static Ref<VertexBuffer> WithSize(i32 size);
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void resize(i32 newSize) = 0;
        virtual void update_sub_data(i32 offset, const void *data, i32 size) = 0;

        virtual void set_layout(const AttributeLayout &layout) = 0;
        mustuse virtual const AttributeLayout &layout() const = 0;
    };

    class IndexBuffer
    {
    public:
        static Ref<IndexBuffer> Create(std::initializer_list<u32> indices);
        static Ref<IndexBuffer> FromSpan(std::span<u32> indices);
        static Ref<IndexBuffer> WithCount(u32 count);
        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void resize(i32 newSize) = 0;
        virtual void update_sub_data(i32 offset, const void *data, i32 size) = 0;

        mustuse virtual u32 count() const = 0;
    };
} // namespace Fussion
