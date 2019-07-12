#include <yunikEngine/manager.hpp>

#include <yunikEngine/window.hpp>

namespace yunikEngine {
    bool Manager::init (void) {
        if (!Window::init()) {
            return false;
        }
        return true;
    }

    void Manager::deinit (void) {
        Window::deinit();
    }

    void Manager::setGlVersion (int major, int minor) {
        gl_major = major;
        gl_minor = minor;
    }

    void Manager::getGlVersion (int& major, int& minor) {
        major = gl_major;
        minor = gl_minor;
    }

    int Manager::gl_major = 4;
    int Manager::gl_minor = 4;
}
