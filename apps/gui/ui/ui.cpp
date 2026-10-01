#include "ui/ui.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <cstdio>

bool Ui::init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        std::fprintf(stderr, "Ui::init: ImGui_ImplGlfw_InitForOpenGL failed\n");
        ImGui::DestroyContext();
        return false;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 330")) {
        std::fprintf(stderr, "Ui::init: ImGui_ImplOpenGL3_Init failed\n");
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        return false;
    }
    ownedContext_ = true;
    return true;
}

void Ui::shutdown() {
    if (!ownedContext_) return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    ownedContext_ = false;
}

void Ui::frame(const std::string& status, int cursorR, int cursorC) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Italian Checkers");
    ImGui::Text("OpenGL 3.3 Core Profile");
    ImGui::Text("Cursore: (%d, %d)", cursorR, cursorC);
    ImGui::Text("Ultimo evento: %s", status.empty() ? "-" : status.c_str());
    ImGui::Separator();
    ImGui::Text("WASD / frecce: muovi il cursore");
    ImGui::Text("R: reset | Esc: esci");
    ImGui::End();

    ImGui::Render();
}
