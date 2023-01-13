#pragma once

#include "Fussion/Math/Matrix4.hpp"
#include "IComponent.hpp"
namespace fussion
{

class Transform : public IComponent
{
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

public:
    Transform() = default;
    mustuse Matrix4 Model();
};

}
