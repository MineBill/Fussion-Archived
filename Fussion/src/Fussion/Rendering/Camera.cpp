#include "Camera.h"

namespace Fussion
{
    Camera2D::Camera2D(f32 width, f32 height, f32 minClip, f32 maxClip)
    {
        TransformT.Scale = Vector3(1.0f);
        m_projectionMatrix = Matrix4::CreateOrthographicOffCenter(-width / 2, width / 2, height / 2, -height / 2, minClip, maxClip);
    }
} // namespace Fussion
