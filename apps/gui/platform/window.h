#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <memory>

using namespace std;

class BoardRenderer;

// Finestra GLFW con contesto OpenGL 3.3 Core.
class Window {
public:
    Window() = default;
    ~Window() { destroy(); }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool create(int width, int height, const std::string& title);
    void destroy();

    bool shouldClose() const;
    void pollEvents();
    void swapBuffers();

    int framebufferWidth() const;
    int framebufferHeight() const;

    GLFWwindow* handle() const { return window_; }

private:
    GLFWwindow* window_ = nullptr;


};
