#pragma once

#include <glm/glm.hpp>

namespace yunikEngine {
    class Window;

    class Camera {
    public:
        enum class Type {
            ORTHO,
            PERSPECTIVE
        };

        void setType (Type newType);

        void setZFar (float newZFar);

        void setZoom (float newZoom); // ortho
        void setFov (float newFov); // perspective

        glm::mat4 getProjectionMatrix (const Window* window) const;

        void setPos (const glm::vec3& newPos);
        void setTarget (const glm::vec3& newTarget);
        void setUp (const glm::vec3& newUp);

        glm::mat4 getViewMatrix (void) const;

    private:
        Type type = Type::PERSPECTIVE;

        float zFar = 100.0f;

        float zoom = 1.0f;
        float fov = 70.0f;

        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);;
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    };
}
