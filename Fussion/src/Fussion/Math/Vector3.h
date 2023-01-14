#pragma once
#include "Fussion/Types.h"
#include <array>
#include <string>

namespace Fussion
{

    struct mustuse Vector3 final {
        std::array<float, 3> data{0.0f, 0.0f, 0.0f};

        inline float x() const
        {
            return data[0];
        }
        inline float y() const
        {
            return data[1];
        }
        inline float z() const
        {
            return data[2];
        }
        inline float &x()
        {
            return data[0];
        }
        inline float &y()
        {
            return data[1];
        }
        inline float &z()
        {
            return data[2];
        }

        Vector3() : data{0.0f, 0.0f, 0.0f}
        {
        }

        Vector3(float x, float y, float z) : data{x, y, z}
        {
        }

        explicit Vector3(float single) : data{single, single, single}
        {
        }

        mustuse float Length() const;

        mustuse float LengthSquared() const;

        Vector3 Normalized() const;

        Vector3 Cross(const Vector3 &other) const;

        mustuse float Dot(const Vector3 &other) const;

        mustuse std::string ToString() const;

        Vector3 operator+(const Vector3 &other) const;
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator/(const Vector3 &other) const;
        Vector3 operator*(const Vector3 &other) const;

        Vector3 operator+(float scalar) const;
        Vector3 operator-(float scalar) const;
        Vector3 operator/(float scalar) const;
        Vector3 operator*(float scalar) const;
    };

} // namespace Fussion

using Vector3 = Fussion::Vector3;
