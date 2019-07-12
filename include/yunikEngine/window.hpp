#pragma once

#include <string>
#include <yunikEngine/manager.hpp>

namespace yunikEngine {
    class Window {
    friend class Manager;

    public:
        ~Window (void);

        bool createWindow (const int& width, const int& height, const std::string& title);

        void render (void);

    private:
        static bool init (void);
        static void deinit (void);

        void* window = nullptr;
    };
}
