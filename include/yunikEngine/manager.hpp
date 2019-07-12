#pragma once

namespace yunikEngine {
    class Manager {
    public:
        static bool init (void);
        static void deinit (void);

        static void setGlVersion (int major, int minor);
        static void getGlVersion (int& major, int& minor);

    private:
        static int gl_major;
        static int gl_minor;
    };
}
