#include "Transform.h"

namespace Fussion
{
    Matrix4 Transform::ModelMatrix()
    {
        auto model = Matrix4::CreateScale(Scale);

        model = model * Matrix4::CreateRotationX(Rotation.x());
        model = model * Matrix4::CreateRotationY(Rotation.y());
        model = model * Matrix4::CreateRotationZ(Rotation.z());

        model = model * Matrix4::CreateTranslation(Position);

        return model;
    }
} // namespace Fussion
