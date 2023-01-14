#include "Camera.hpp"
#include "Fussion/Math/Matrix4.h"

using namespace editor;

Camera::Camera()
{
    m_projection = Matrix::CreatePerspectiveOffCenter();
}
