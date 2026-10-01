#include "platform/window.h"

#include <glad/glad.h>

#include <cstdio>

bool Window::create(int width, int height, const std::string& title) {
    // OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window_) {
        std::fprintf(stderr, "Window::create: glfwCreateWindow failed\n");
        return false;
    }
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);  // vsync

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::fprintf(stderr, "Window::create: gladLoadGLLoader failed\n");
        destroy();
        return false;
    }

    return true;
}

void Window::destroy() {
    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
}

bool Window::shouldClose() const {
    return window_ && glfwWindowShouldClose(window_) == GLFW_TRUE;
}

void Window::pollEvents() {
    if (window_) glfwPollEvents();
}

void Window::swapBuffers() {
    if (window_) glfwSwapBuffers(window_);
}

int Window::framebufferWidth() const {
    int w = 0, h = 0;
    if (window_) glfwGetFramebufferSize(window_, &w, &h);
    return w;
}

int Window::framebufferHeight() const {
    int w = 0, h = 0;
    if (window_) glfwGetFramebufferSize(window_, &w, &h);
    return h;
}
