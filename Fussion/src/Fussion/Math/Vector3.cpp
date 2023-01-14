#include "Vector3.h"
#include <cmath>
#include <sstream>

using namespace Fussion;

float Vector3::Length() const
{
    return sqrtf(LengthSquared());
}

float Vector3::LengthSquared() const
{
    return x() * x() + y() * y() + z() * z();
}

Vector3 Vector3::Normalized() const
{
    auto length = Length();
    return *this / length;
}

Vector3 Vector3::Cross(const Vector3 &other) const
{
    return {y() * other.z() - other.y() * z(), z() * other.x() - other.z() * x(), x() * other.y() - other.x() * y()};
}

std::string Vector3::ToString() const
{
#if FORMAT_IS_FINALLY_IN_THE_FUCKING_STANDARD
    return std::format("Vector3({}, {}, {})", x(), y(), z());
#else
    std::stringstream ss;
    ss << "Vector3(" << x() << ", " << y() << ", " << z() << ")";
    return ss.str();
#endif
}

float Vector3::Dot(const Vector3 &other) const
{
    return x() * other.x() + y() * other.y() + z() * other.z();
}

Vector3 Vector3::operator+(const Vector3 &other) const
{
    return {x() + other.x(), y() + other.y(), z() + other.z()};
}

Vector3 Vector3::operator-(const Vector3 &other) const
{
    return {x() - other.x(), y() - other.y(), z() - other.z()};
}

Vector3 Vector3::operator/(const Vector3 &other) const
{
    return {x() / other.x(), y() / other.y(), z() / other.z()};
}

Vector3 Vector3::operator*(const Vector3 &other) const
{
    return {x() * other.x(), y() * other.y(), z() * other.z()};
}

Vector3 Vector3::operator+(float scalar) const
{
    return {x() + scalar, y() + scalar, z() + scalar};
}

Vector3 Vector3::operator-(float scalar) const
{
    return {x() - scalar, y() - scalar, z() - scalar};
}

Vector3 Vector3::operator*(float scalar) const
{
    return {x() * scalar, y() * scalar, z() * scalar};
}

Vector3 Vector3::operator/(float scalar) const
{
    return {x() / scalar, y() / scalar, z() / scalar};
}
