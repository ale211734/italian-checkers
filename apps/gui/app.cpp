#include "app.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>

namespace {

void keyCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }
    if (auto* keyboard = static_cast<Keyboard*>(glfwGetWindowUserPointer(window))) {
        keyboard->handleKey(key, action);
    }
}

}  // namespace

bool App::init() {
    board = make_unique<BoardRenderer>();

    if (!glfw_.init()) return false;

    if (!window_.create(1280, 720, "Italian Checkers")) return false;

    glfwSetWindowUserPointer(window_.handle(), &keyboard_);
    glfwSetKeyCallback(window_.handle(), keyCallback);

    if (!board->init(window_.framebufferWidth(), window_.framebufferHeight())) return false;
    if (!ui_.init(window_.handle())) return false;
    return true;
}

void App::pollGameInput() {
    if (keyboard_.isPressed(GLFW_KEY_W) || keyboard_.isPressed(GLFW_KEY_UP)) {
        cursorR_ = (cursorR_ + 7) % 8;
        lastEvent_ = Keyboard::keyName(keyboard_.isPressed(GLFW_KEY_W) ? GLFW_KEY_W : GLFW_KEY_UP);
    }
   
    keyboard_.endFrame();
}

void App::frame() {
    window_.pollEvents();
    pollGameInput();

    ui_.frame(lastEvent_, cursorR_, cursorC_);

    const int w = window_.framebufferWidth();
    const int h = window_.framebufferHeight();
    glViewport(0, 0, w, h);
    camera_.updateProjection(w, h);
    glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    board->render(camera_, cursorR_, cursorC_);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    window_.swapBuffers();
}

int App::run() {
    while (!window_.shouldClose()) {
        frame();
    }
    ui_.shutdown();
    board->shutdown();
    return 0;
}
