#pragma once

#include "input/keyboard.h"
#include "platform/glfw_context.h"
#include "platform/window.h"
#include "renderer/camera.h"
#include "renderer/board_renderer.h"
#include "ui/ui.h"

// Composizione delle parti e game loop.
class App {
public:
    bool init();
    int run();

private:
    void frame();
    void pollGameInput();

    GlfwContext glfw_;
    Window window_;
    Keyboard keyboard_;
    Ui ui_;
    Camera camera_;

    // Stato di gioco (demo: cursore su griglia 8x8).
    int cursorR_ = 0;
    int cursorC_ = 0;
    std::string lastEvent_;
    unique_ptr<BoardRenderer> board;
};
