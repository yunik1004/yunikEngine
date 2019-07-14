#include <iostream>
#include <yunikEngine/manager.hpp>
#include <yunikEngine/window.hpp>
#include <yunikEngine/scene.hpp>

class testScene : public yunikEngine::Scene {
    public:
    ~testScene (void) {}
    yunikEngine::Scene* update (void) {
        return this;
    }
};

int main (void) {
    if (!yunikEngine::Manager::init()) {
        return -1;
    }

    yunikEngine::Window w;
    w.createWindow(1064, 768, "Hello world!");

    w.setScene(new testScene());

    w.render();

    yunikEngine::Manager::deinit();
    return 0;
}
