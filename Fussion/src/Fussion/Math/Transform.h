#pragma once
#include "Fussion/Math/Matrix4.h"
#include "Fussion/Math/Vector3.h"

namespace Fussion
{
    class Transform
    {
        Matrix4 m_modelCache;

    public:
        Vector3 Position;
        Vector3 Rotation;
        Vector3 Scale;

        Matrix4 ModelMatrix();
    };
} // namespace Fussion
