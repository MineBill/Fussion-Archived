#pragma once

namespace Fussion
{
    enum class VertexType {
        Vector2,
        Vector3,
        Vector4,
    };

    class VertexBuffer
    {
    public:
        static Ptr<VertexBuffer> Create(std::vector<float> const &vertices, std::vector<VertexType> const &usage);
        static Ptr<VertexBuffer> WithSize(i32 size, std::vector<VertexType> const &usage);
        virtual ~VertexBuffer() = default;

        virtual void Use() const = 0;
        virtual void Resize(i32 new_size) = 0;
        virtual void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) = 0;
    };

    class IndexBuffer
    {
    public:
        static Ptr<IndexBuffer> Create(std::vector<u32> const &indices);
        static Ptr<IndexBuffer> WithSize(i32 size);
        virtual ~IndexBuffer() = default;

        virtual void Use() const = 0;
        virtual void Resize(i32 new_size) = 0;
        virtual void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) = 0;
    };
} // namespace Fussion
