#pragma once

namespace Fussion
{
    class Transform
    {
        glm::mat4 m_modelCache;

    public:
        glm::vec3 Position;
        glm::vec3 Rotation;
        glm::vec3 Scale;

        mustuse glm::mat4 ModelMatrix() const;
    };
} // namespace Fussion
