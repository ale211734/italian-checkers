#pragma once

#include <GLFW/glfw3.h>

// RAII wrapper per glfwInit()/glfwTerminate().
class GlfwContext {
public:
    GlfwContext() = default;
    ~GlfwContext() { shutdown(); }

    GlfwContext(const GlfwContext&) = delete;
    GlfwContext& operator=(const GlfwContext&) = delete;

    bool init() {
        if (initialized_) return true;
        initialized_ = glfwInit() == GLFW_TRUE;
        return initialized_;
    }

    void shutdown() {
        if (initialized_) {
            glfwTerminate();
            initialized_ = false;
        }
    }

private:
    bool initialized_ = false;
};
