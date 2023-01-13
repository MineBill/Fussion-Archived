#include "Transform.hpp"

using namespace fussion;

Matrix4 Transform::Model()
{
    auto model = Matrix::CreateScale(scale);
    model = model * Matrix::CreateRotationX(rotation.x());
    model = model * Matrix::CreateRotationY(rotation.y());
    model = model * Matrix::CreateRotationZ(rotation.z());
    model = model * Matrix::CreateTranslation(position);
    return model;
}