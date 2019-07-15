#include <yunikEngine/camera.hpp>

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <yunikEngine/window.hpp>

namespace yunikEngine {
    void Camera::setType (const Type newType) {
        type = newType;
    }

    void Camera::setZFar (const float newZFar) {
        zFar = newZFar;
    }

    void Camera::setZoom (const float newZoom) {
        zoom = newZoom;
    }

    void Camera::setFov (const float newFov) {
        fov = newFov;
    }

    glm::mat4 Camera::getProjectionMatrix (const Window* window) const {
        int width, height;
        window->getViewportSize(width, height);

        switch (type) {
            case Type::ORTHO:
            {
                float proj_width_quart = (float)width / (2.0f * zoom);
                float proj_height_quart = (float)height / (2.0f * zoom);

                return glm::ortho(-proj_width_quart, proj_width_quart, -proj_height_quart, proj_height_quart, 0.0f, zFar);
            }
            case Type::PERSPECTIVE:
            {
                return glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, zFar);
            }
        }

        return glm::mat4(0.0f); // error
    }

    void Camera::setPos (const glm::vec3& newPos) {
        pos = newPos;
    }

    void Camera::setTarget (const glm::vec3& newTarget) {
        target = newTarget;
    }

    void Camera::setUp (const glm::vec3& newUp) {
        up = newUp;
    }

    glm::mat4 Camera::getViewMatrix (void) const {
        return glm::lookAt(pos, target, up);
    }
}
