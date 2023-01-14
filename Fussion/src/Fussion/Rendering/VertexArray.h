#pragma once
#include "Fussion/Types.h"
#include <vector>

namespace Fussion
{

    enum class VertexType;
    class VertexArray
    {
        virtual void UpdateVertexBufferSubDataRaw(i32 offset, const void *new_data, i32 size) = 0;
        virtual void UpdateIndexBufferSubDataRaw(i32 offset, const void *new_data, i32 size) = 0;

    public:
        virtual ~VertexArray() = default;

        static Ptr<VertexArray> Create(std::vector<float> const &vertices, std::vector<VertexType> const &usage);
        static Ptr<VertexArray> Create(std::vector<float> const &vertices, const std::vector<u32> &indices,
                                       std::vector<VertexType> const &usage);
        static Ptr<VertexArray> WithSize(i32 vertex_size, i32 index_size, std::vector<VertexType> const &usage);

        virtual void Use() const = 0;

        virtual void ResizeVertexBuffer(i32 new_size) = 0;
        virtual void ResizeIndexBuffer(i32 new_size) = 0;

        template<typename T>
        void UpdateVertexBufferSubData(i32 offset, T *data, i32 size)
        {
            UpdateVertexBufferSubDataRaw(offset, data, static_cast<i32>(sizeof(T)) * size);
        }

        template<typename T>
        void UpdateVertexBufferSubData(i32 offset, const std::vector<T> &new_data)
        {
            UpdateVertexBufferSubDataRaw(offset, new_data.data(), static_cast<i32>(sizeof(T)) * new_data.size());
        }

        template<typename T>
        void UpdateIndexBufferSubData(i32 offset, const T *data, i32 size)
        {
            UpdateIndexBufferSubDataRaw(offset, data, static_cast<i32>(sizeof(T)) * size);
        }

        template<typename T>
        void UpdateIndexBufferSubData(i32 offset, const std::vector<T> &new_data)
        {
            UpdateIndexBufferSubDataRaw(offset, new_data.data(), static_cast<i32>(sizeof(T)) * new_data.size());
        }

        mustuse virtual i32 Count() const = 0;
    };

} // namespace Fussion
