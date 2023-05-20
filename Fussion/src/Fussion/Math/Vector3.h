#pragma once
#include "Fussion/Core/Types.h"
#include <array>
#include <string>

namespace Fussion
{
    struct mustuse Vector3 final {
#if 1
        std::array<float, 3> data{0.0f, 0.0f, 0.0f};

        mustuse inline float x() const { return data[0]; }
        mustuse inline float y() const { return data[1]; }
        mustuse inline float z() const { return data[2]; }
        inline float &x() { return data[0]; }
        inline float &y() { return data[1]; }
        inline float &z() { return data[2]; }

        Vector3() : data{0.0f, 0.0f, 0.0f} {}

        Vector3(float x, float y, float z) : data{x, y, z} {}

        explicit Vector3(float single) : data{single, single, single} {}
#else
        float x{}, y{}, z{};

        Vector3() : x{0.0f}, y{0.0f}, z{0.0f} {}

        Vector3(float x, float y, float z) : data{x, y, z} {}

        explicit Vector3(float single) : data{single, single, single} {}
#endif

        mustuse float length() const;
        mustuse float length_squared() const;
        mustuse Vector3 normalized() const;
        mustuse Vector3 cross(const Vector3 &other) const;
        mustuse float dot(const Vector3 &other) const;
        mustuse std::string to_string() const;

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
