#pragma once

#include <GLFW/glfw3.h>

#include <set>
#include <string>

// Stato tastiera lato GLFW (indipendente da ImGui).
// Chiamare endFrame() una volta per frame dopo aver consumato isPressed().
class Keyboard {
public:
    // Da invocare dal callback GLFW.
    void handleKey(int key, int action) {
        if (action == GLFW_PRESS) {
            held_.insert(key);
            pressed_.insert(key);
        } else if (action == GLFW_RELEASE) {
            held_.erase(key);
        }
    }

    bool isHeld(int key) const { return held_.count(key) != 0; }
    bool isPressed(int key) const { return pressed_.count(key) != 0; }

    void endFrame() { pressed_.clear(); }

    static std::string keyName(int key);

private:
    std::set<int> held_;    // tasti attualmente premuti
    std::set<int> pressed_; // premuti in questo frame
};
