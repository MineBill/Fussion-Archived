#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

namespace Fussion
{
    glm::mat4 Transform::ModelMatrix() const
    {
        auto model = glm::translate(glm::mat4(1.0f), Scale);

        model = glm::rotate(model, Rotation.z, {0, 0, 1});
        model = glm::rotate(model, Rotation.y, {0, 1, 0});
        model = glm::rotate(model, Rotation.x, {1, 0, 0});

        model = glm::translate(model, Position);

        return model;
    }
} // namespace Fussion
