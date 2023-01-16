#pragma once
#include "Fussion/Math/Matrix4.h"
#include "Fussion/Math/Transform.h"

namespace Fussion
{
    class Camera2D
    {
        Matrix4 m_projectionMatrix;

    public:
        Transform TransformT;

        Camera2D(f32 width, f32 height, f32 minClip = 0.1f, f32 maxClip = 100.0f);

        mustuse const Matrix4 &GetProjection() const
        {
            return m_projectionMatrix;
        }

        mustuse Matrix4 GetView()
        {
            return TransformT.ModelMatrix();
        }
    };
} // namespace Fussion
