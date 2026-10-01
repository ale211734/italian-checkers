#include "input/keyboard.h"

std::string Keyboard::keyName(int key) {
    switch (key) {
        case GLFW_KEY_W: return "W";
        case GLFW_KEY_A: return "A";
        case GLFW_KEY_S: return "S";
        case GLFW_KEY_D: return "D";
        case GLFW_KEY_UP: return "Up";
        case GLFW_KEY_DOWN: return "Down";
        case GLFW_KEY_LEFT: return "Left";
        case GLFW_KEY_RIGHT: return "Right";
        case GLFW_KEY_R: return "R";
        case GLFW_KEY_ESCAPE: return "Esc";
        default: return std::to_string(key);
    }
}
