#include "renderer/piece_renderer.h"

#include <vector>
#include <cmath>
#include <cstdio>
#include <glm/gtc/matrix_transform.hpp>

namespace {

const char* kVertexSrc = R"(#version 330 core
layout(location = 0) in vec2 aPos;

uniform mat4 uMVP;
uniform vec2 uOffset;
uniform float uScale;

void main() {
    vec2 pos = aPos * uScale + uOffset;
    gl_Position = uMVP * vec4(pos, 0.0f, 1.0f);
}
)";

const char* kFragmentSrc = R"(#version 330 core
out vec4 FragColor;
uniform vec4 uColor;

void main() {
    FragColor = uColor;
}
)";

}  // namespace


bool PieceRenderer::init() {
    if (!shader_.load(kVertexSrc, kFragmentSrc)) return false;

    // Genera geometria cerchio (approssimata a triangoli a ventaglio)
    const int segments = 32;
    std::vector<float> vertices;
    
    float cx = 0.0f;
    float cy = 0.0f;

    for (int i = 0; i < segments; ++i) {
        float angle1 = 2.0f * 3.1415926535f * static_cast<float>(i) / static_cast<float>(segments);
        float angle2 = 2.0f * 3.1415926535f * static_cast<float>(i + 1) / static_cast<float>(segments);

        // Triangolo: Centro, Punto 1, Punto 2
        vertices.push_back(cx);
        vertices.push_back(cy);

        vertices.push_back(std::cos(angle1));
        vertices.push_back(std::sin(angle1));

        vertices.push_back(std::cos(angle2));
        vertices.push_back(std::sin(angle2));
    }

    vertexCount_ = static_cast<int>(vertices.size() / 2);

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    return true;
}

void PieceRenderer::shutdown() {
    if (vao_) glDeleteVertexArrays(1, &vao_);
    if (vbo_) glDeleteBuffers(1, &vbo_);
    shader_.shutdown();
    vao_ = vbo_ = 0;
    vertexCount_ = 0;
}

void PieceRenderer::render(const Camera& camera, const dama::GameState& gameState) {
    shader_.use();

    glm::mat4 mvp = camera.viewProjectionMatrix();
    shader_.setMat4("uMVP", mvp);

    glBindVertexArray(vao_);

    // Raggio/scala della pedina rispetto alla dimensione di una casella (1.0)
    const float pieceScale = 0.38f; 

    for (int r = 0; r < dama::kBoardSize; ++r) {
        for (int c = 0; c < dama::kBoardSize; ++c) {
            dama::Piece p = gameState.board[r][c];
            if (p == dama::Piece::None) continue;

            // Calcolo posizione mondiale del centro della casella (r, c)
            float worldX = static_cast<float>(c) + 0.5f - 4.0f;
            float worldY = 4.0f - (static_cast<float>(r) + 0.5f);

            shader_.setVec2("uOffset", worldX, worldY);
            shader_.setFloat("uScale", pieceScale);

            // Colore della pedina
            float color[4];
            if (p == dama::Piece::White || p == dama::Piece::WhiteKing) {
                color[0] = 0.92f; color[1] = 0.92f; color[2] = 0.92f; color[3] = 1.0f; // Bianco
            } else {
                color[0] = 0.18f; color[1] = 0.18f; color[2] = 0.18f; color[3] = 1.0f; // Nero
            }

            glUniform4fv(glGetUniformLocation(shader_.id(), "uColor"), 1, color);

            glDrawArrays(GL_TRIANGLES, 0, vertexCount_);
        }
    }
}
