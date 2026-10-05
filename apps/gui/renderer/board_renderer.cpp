#include "renderer/board_renderer.h"

#include <array>
#include <cstdio>

namespace {

const char* kVertexSrc = R"(#version 330 core
layout(location = 0) in vec2 aPos; // quad [0,1]x[0,1]

uniform mat4 uMVP;

out vec2 vUV;

void main() {
    vUV = aPos;
    gl_Position = uMVP * vec4(aPos - 0.5f, 0.0f, 1.0f);
}
)";

const char* kFragmentSrc = R"(#version 330 core
in vec2 vUV;
out vec4 FragColor;

uniform int uCursorR;
uniform int uCursorC;

void main() {
    vec2 boardCoord = vUV * 8.0f;
    
    int c = int(floor(boardCoord.x));
    int r = int(floor((1.0f - vUV.y) * 8.0f));

    c = clamp(c, 0, 7);
    r = clamp(r, 0, 7);

    vec4 color;
    if (r == uCursorR && c == uCursorC) {
        color = vec4(0.95f, 0.80f, 0.25f, 1.0f);
    } else if ((r + c) % 2 == 0) {
        color = vec4(0.42f, 0.30f, 0.20f, 1.0f);
        
    } else {
        color = vec4(0.87f, 0.72f, 0.53f, 1.0f);
    }
    FragColor = color;
}
)";

}  // namespace

bool BoardRenderer::init(int /*width*/, int /*height*/) {
    if (!shader_.load(kVertexSrc, kFragmentSrc)) return false;

    const std::array<float, 12> quad = {
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
    };

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, quad.size() * sizeof(float), quad.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    return true;
}

void BoardRenderer::shutdown() {
    if (vao_) glDeleteVertexArrays(1, &vao_);
    if (vbo_) glDeleteBuffers(1, &vbo_);
    shader_.shutdown();
    vao_ = vbo_ = 0;
}

void BoardRenderer::render(const Camera& camera, int cursorR, int cursorC) {
    shader_.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(8.0f, 8.0f, 1.0f));

    glm::mat4 mvp = camera.viewProjectionMatrix() * model;

    shader_.setMat4("uMVP", mvp);
    shader_.setInt("uCursorR", cursorR);
    shader_.setInt("uCursorC", cursorC);

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
