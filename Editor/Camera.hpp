#pragma once
#include "Fussion/Math/Matrix4.h"
#include "Fussion/Math/Vector3.h"

namespace editor
{

class Camera final
{
    Vector3 m_position {};
    Vector3 m_rotation {};
    Vector3 m_scale {};

    Matrix m_projection {};

public:
    Camera();

    mustuse Vector3 Position() const { return m_position; }
};

}
