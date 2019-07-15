#pragma once

#include <string>

namespace yunikEngine {
    class Manager;
    class Scene;

    class Window {
    friend class Manager;

    public:
        ~Window (void);

        bool createWindow (const int width, const int height, const std::string& title);

        void setScene (Scene* newScene);
        void deleteScene (void);

        void render (void);

        void getViewportSize (int& width, int& height) const;

    private:
        static bool init (void);
        static void deinit (void);

        void* window = nullptr;

        Scene* scene = nullptr;
    };
}
