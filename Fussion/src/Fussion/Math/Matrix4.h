#pragma once
#include "Fussion/Core/Types.h"
#include "Vector3.h"
#include <array>

namespace Fussion
{

    struct mustuse Matrix4 final {
        std::array<float, 16> data{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

        float operator()(std::size_t row, std::size_t column) const;
        float &operator()(std::size_t row, std::size_t column);

        Matrix4 operator*(const Matrix4 &other) const;

        static Matrix4 CreateRotationX(float angle);
        static Matrix4 CreateRotationY(float angle);
        static Matrix4 CreateRotationZ(float angle);

        static Matrix4 CreateTranslation(Vector3 translation);
        static Matrix4 CreateScale(Vector3 scale);

        static Matrix4 CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float depth_near,
                                                  float depth_far);
        static Matrix4 CreatePerspectiveFieldOfView(f32 fov, f32 aspect, f32 depth_near, f32 depth_far);

        static Matrix4 CreateOrthographicOffCenter(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
    };

} // namespace Fussion

using Matrix = Fussion::Matrix4;
