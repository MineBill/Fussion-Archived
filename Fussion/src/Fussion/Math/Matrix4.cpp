#include "Matrix4.hpp"
#include <assert.hpp>
#include <cmath>

using namespace fussion;

float Matrix4::operator()(std::size_t row, std::size_t column) const
{
    return data[column + row * 4];
}

float &Matrix4::operator()(std::size_t row, std::size_t column)
{
    return data[column + row * 4];
}

Matrix4 Matrix4::operator*(const Matrix4 &o) const
{
    auto result = Matrix4 {};

    result.data = {
        (*this)(0, 0) * o(0, 0) + (*this)(0, 1) * o(1, 0) + (*this)(0, 2) * o(2, 0) + (*this)(0, 3) * o(3, 0),
        (*this)(0, 0) * o(0, 1) + (*this)(0, 1) * o(1, 1) + (*this)(0, 2) * o(2, 1) + (*this)(0, 3) * o(3, 1),
        (*this)(0, 0) * o(0, 2) + (*this)(0, 1) * o(1, 2) + (*this)(0, 2) * o(2, 2) + (*this)(0, 3) * o(3, 2),
        (*this)(0, 0) * o(0, 3) + (*this)(0, 1) * o(1, 3) + (*this)(0, 2) * o(2, 3) + (*this)(0, 3) * o(3, 3),

        (*this)(1, 0) * o(0, 0) + (*this)(1, 1) * o(1, 0) + (*this)(1, 2) * o(2, 0) + (*this)(1, 3) * o(3, 0),
        (*this)(1, 0) * o(0, 1) + (*this)(1, 1) * o(1, 1) + (*this)(1, 2) * o(2, 1) + (*this)(1, 3) * o(3, 1),
        (*this)(1, 0) * o(0, 2) + (*this)(1, 1) * o(1, 2) + (*this)(1, 2) * o(2, 2) + (*this)(1, 3) * o(3, 2),
        (*this)(1, 0) * o(0, 3) + (*this)(1, 1) * o(1, 3) + (*this)(1, 2) * o(2, 3) + (*this)(1, 3) * o(3, 3),

        (*this)(2, 0) * o(0, 0) + (*this)(2, 1) * o(1, 0) + (*this)(2, 2) * o(2, 0) + (*this)(2, 3) * o(3, 0),
        (*this)(2, 0) * o(0, 1) + (*this)(2, 1) * o(1, 1) + (*this)(2, 2) * o(2, 1) + (*this)(2, 3) * o(3, 1),
        (*this)(2, 0) * o(0, 2) + (*this)(2, 1) * o(1, 2) + (*this)(2, 2) * o(2, 2) + (*this)(2, 3) * o(3, 2),
        (*this)(2, 0) * o(0, 3) + (*this)(2, 1) * o(1, 3) + (*this)(2, 2) * o(2, 3) + (*this)(2, 3) * o(3, 3),

        (*this)(3, 0) * o(0, 0) + (*this)(3, 1) * o(1, 0) + (*this)(3, 2) * o(2, 0) + (*this)(3, 3) * o(3, 0),
        (*this)(3, 0) * o(0, 1) + (*this)(3, 1) * o(1, 1) + (*this)(3, 2) * o(2, 1) + (*this)(3, 3) * o(3, 1),
        (*this)(3, 0) * o(0, 2) + (*this)(3, 1) * o(1, 2) + (*this)(3, 2) * o(2, 2) + (*this)(3, 3) * o(3, 2),
        (*this)(3, 0) * o(0, 3) + (*this)(3, 1) * o(1, 3) + (*this)(3, 2) * o(2, 3) + (*this)(3, 3) * o(3, 3)
    };

    return result;
}

Matrix4 Matrix4::CreateRotationX(float angle)
{
    auto result = Matrix4();
    float c = cosf(angle);
    float s = sinf(angle);
    result(1, 1) = c;
    result(1, 2) = s;
    result(2, 1) = -s;
    result(2, 2) = c;
    return result;
}

Matrix4 Matrix4::CreateRotationY(float angle)
{
    auto result = Matrix4();
    float c = cosf(angle);
    float s = sinf(angle);
    result(0, 0) = c;
    result(0, 2) = -s;
    result(2, 0) = s;
    result(2, 2) = c;
    return result;
}

Matrix4 Matrix4::CreateRotationZ(float angle)
{
    auto result = Matrix4();
    float c = cosf(angle);
    float s = sinf(angle);
    result(0, 0) = c;
    result(0, 1) = s;
    result(1, 0) = -s;
    result(1, 1) = c;
    return result;
}

Matrix4 Matrix4::CreateTranslation(Vector3 translation)
{
    auto result = Matrix4();
    result(3, 0) = translation.x();
    result(3, 1) = translation.y();
    result(3, 2) = translation.z();
    return result;
}

Matrix4 Matrix4::CreateScale(Vector3 scale)
{
    auto result = Matrix4();
    result(0, 0) = scale.x();
    result(1, 1) = scale.y();
    result(2, 2) = scale.z();
    return result;
}

Matrix4 Matrix4::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float depth_near, float depth_far)
{
    ASSERT(depth_near > 0);
    ASSERT(depth_far > 0);

    auto result = Matrix4();

    float num1 = 2.0f * depth_near / (right - left);
    float num2 = 2.0f * depth_near / (top - bottom);
    float num3 = (right + left) / (right - left);
    float num4 = (top + bottom) / (top - bottom);
    float num5 = -(depth_far + depth_near) / (depth_far - depth_near);
    float num6 = -(2.0f * depth_far * depth_near) / (depth_far - depth_near);
    result(0, 0) = num1;
    result(0, 1) = 0.0f;
    result(0, 2) = 0.0f;
    result(0, 3) = 0.0f;
    result(1, 0) = 0.0f;
    result(1, 1) = num2;
    result(1, 2) = 0.0f;
    result(1, 3) = 0.0f;
    result(2, 0) = num3;
    result(2, 1) = num4;
    result(2, 2) = num5;
    result(2, 3) = -1.0f;
    result(3, 0) = 0.0f;
    result(3, 1) = 0.0f;
    result(3, 2) = num6;
    result(3, 3) = 0.0f;
    return result;
}

Matrix4 Matrix4::CreatePerspectiveFieldOfView(f32 fov, f32 aspect, f32 depth_near, f32 depth_far)
{
    ASSERT(fov > 0 && fov <= std::numbers::pi_v<f32>, "Fov must be within range");
    ASSERT(aspect > 0);
    ASSERT(depth_near > 0);
    ASSERT(depth_far > 0);

    auto max_y = depth_near * tanf(0.5f * fov);
    auto min_y = -max_y;
    auto min_x = min_y * aspect;
    auto max_x = max_y * aspect;

    return CreatePerspectiveOffCenter(min_x, max_x, min_y, max_y, depth_near, depth_far);
}

Matrix4 Matrix4::CreateOrthographicOffCenter(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
{
    auto result = Matrix4();

    auto num1 = (1.0f / (right - left));
    auto num2 = (1.0f / (top - bottom));
    auto num3 = (1.0f / (far - near));
    result(0, 0) = 2.0f * num1;
    result(1, 1) = 2.0f * num2;
    result(2, 2) = -2.0f * num3;
    result(3, 0) = -(right + left) * num1;
    result(3, 1) = -(top + bottom) * num2;
    result(3, 2) = -(far + near) * num3;

    return result;
}
