#pragma once
#include <Fussion/Core.h>

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

    static i32 VertexElementTypeSize(VertexElementType type)
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

    static i32 VertexElementTypeCount(VertexElementType type)
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
            : Type(type), Name(name), Size(VertexElementTypeSize(type)), Count(VertexElementTypeCount(type)), Offset(0)
        {
        }
    };

    class AttributeLayout
    {
        std::vector<Attribute> m_attributes{};
        i32 m_stride{0};

        void CalculateOffsetAndString()
        {
            for (auto &attribute : m_attributes) {
                attribute.Offset = m_stride;
                m_stride += attribute.Size;
            }
        }

    public:
        AttributeLayout(const std::initializer_list<Attribute> &attributes) : m_attributes(attributes)
        {
            CalculateOffsetAndString();
        }

        mustuse inline i32 GetString() const
        {
            return m_stride;
        }

        mustuse inline const std::vector<Attribute> &GetAttributes() const
        {
            return m_attributes;
        }
    };

    class VertexBuffer
    {
    public:
        static Ref<VertexBuffer> Create(std::vector<float> const &vertices);
        static Ref<VertexBuffer> WithSize(i32 size);
        virtual ~VertexBuffer() = default;

        virtual void Use() const = 0;
        virtual void Resize(i32 newSize) = 0;
        virtual void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) = 0;

        virtual void SetLayout(const AttributeLayout &layout) = 0;
        mustuse virtual const AttributeLayout &GetLayout() const = 0;
    };

    class IndexBuffer
    {
    public:
        static Ref<IndexBuffer> Create(std::vector<u32> const &indices);
        static Ref<IndexBuffer> WithSize(i32 count);
        virtual ~IndexBuffer() = default;

        virtual void Use() const = 0;
        virtual void Resize(i32 newSize) = 0;
        virtual void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) = 0;

        mustuse virtual i32 Count() const = 0;
    };
} // namespace Fussion
