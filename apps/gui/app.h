#pragma once

#include "input/keyboard.h"
#include "platform/glfw_context.h"
#include "platform/window.h"
#include "renderer/camera.h"
#include "renderer/board_renderer.h"
#include "renderer/piece_renderer.h"
#include "ui/ui.h"
#include "core/engine.h"
#include <memory>

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

    int cursorR_ = 0;
    int cursorC_ = 0;
    std::string lastEvent_;

    std::unique_ptr<BoardRenderer> boardRenderer_;
    std::unique_ptr<PieceRenderer> pieceRenderer_;
    dama::GameState gameState;
};
