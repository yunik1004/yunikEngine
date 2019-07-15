#include <yunikEngine/scene.hpp>

#include <yunikEngine/window.hpp>

namespace yunikEngine {
    void Scene::setWindow (Window* newWindow) {
        window = newWindow;
    }

    Window* Scene::getWindow (void) const {
        return window;
    }
}
