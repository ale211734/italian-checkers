#pragma once

#include <glad/glad.h>
#include "renderer/camera.h"
#include "renderer/shader.h"
#include "core/engine.h"

// Renderer per le pedine e dame, con geometria generata proceduralmente (cerchi).
class PieceRenderer {
public:
    bool init();
    void shutdown();
    void render(const Camera& camera, const dama::Position& position);

private:
    Shader shader_;
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
    int vertexCount_ = 0;
};
