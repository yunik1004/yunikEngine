#include <yunikEngine/window.hpp>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <yunikEngine/manager.hpp>
#include <yunikEngine/scene.hpp>

namespace yunikEngine {
    Window::~Window (void) {
        delete scene;

        if (window) {
            glfwDestroyWindow(static_cast<GLFWwindow*>(window));
        }
    }

    bool Window::createWindow (const int width, const int height, const std::string& title) {
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            fprintf_s(stderr, "GLFW error: Failed to create window\n");
            return false;
        }

        GLFWwindow* glWindow = static_cast<GLFWwindow*>(window);

        glfwMakeContextCurrent(glWindow);

        /* Initialize glew */
        GLenum errorCode = glewInit();
        if (errorCode != GLEW_OK) {
            fprintf_s(stderr, "GLEW error: Failed to initialize glew. %s\n", glewGetErrorString(errorCode));
            glfwDestroyWindow(glWindow);
            return false;
        }

        /* Check OpenGL version */
        int gl_major, gl_minor;
        Manager::getGlVersion(gl_major, gl_minor);
        char gl_version[15];
        sprintf_s(gl_version, "GL_VERSION_%d_%d", gl_major, gl_minor);
        if (!glewIsSupported(gl_version)) {
            fprintf_s(stderr, "OpenGL error: %s is not available\n", gl_version);
            glfwDestroyWindow(glWindow);
            return false;
        }

        /* Set OpenGL options */
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return true;
    }

    void Window::setScene (Scene* newScene) {
        delete scene;
        scene = newScene;
    }

    void Window::deleteScene (void) {
        delete scene;
        scene = nullptr;
    }

    void Window::render (void) {
        GLFWwindow* glWindow = static_cast<GLFWwindow*>(window);
        while (!glfwWindowShouldClose(glWindow)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (scene) {
                auto newScene = scene->update();
                if (scene != newScene) {
                    setScene(newScene);
                }
            }

            glfwSwapBuffers(glWindow);
            glfwPollEvents();
        }
    }

    void Window::getViewportSize (int& width, int& height) const {
        GLFWwindow* glWindow = static_cast<GLFWwindow*>(window);
        glfwGetWindowSize(glWindow, &width, &height);
    }

    bool Window::init (void) {
        if (!glfwInit()) {
            fprintf_s(stderr, "GLFW error: Failed to initialize glfw\n");
            return false;
        }

        /* OpenGL version */
        int gl_major, gl_minor;
        Manager::getGlVersion(gl_major, gl_minor);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        return true;
    }

    void Window::deinit (void) {
        glfwTerminate();
    }
}
