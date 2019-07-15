#pragma once

namespace yunikEngine {
    class Window;

    class Scene {
    public:
        virtual ~Scene (void) {}
        virtual Scene* update (void) = 0;

        void setWindow (Window* newWindow);
        Window* getWindow (void);

    private:
        Window* window = nullptr;
    };
}
