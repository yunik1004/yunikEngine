#include <iostream>
#include <yunikEngine/manager.hpp>
#include <yunikEngine/window.hpp>

int main (void) {
    if (!yunikEngine::Manager::init()) {
        return -1;
    }

    yunikEngine::Window w;
    w.createWindow(1064, 768, "Hello world!");
    w.render();

    yunikEngine::Manager::deinit();
    return 0;
}
