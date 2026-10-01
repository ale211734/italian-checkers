#pragma once

#include <GLFW/glfw3.h>

#include <string>

// Strato UI Dear ImGui: init/shutdown dei backend e disegno del frame.
class Ui {
public:
    bool init(GLFWwindow* window);
    void shutdown();

    // Disegna il frame ImGui (chiamare tra NewFrame/Render della pipeline).
    void frame(const std::string& status, int cursorR, int cursorC);

private:
    bool ownedContext_ = false;
};
