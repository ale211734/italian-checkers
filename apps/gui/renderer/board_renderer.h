#pragma once

#include <glad/glad.h>
#include "renderer/camera.h"

// Scacchiera 8x8 renderizzata su un singolo quad con OpenGL 3.3 e Camera (MVP).
class BoardRenderer {
public:
    bool init(int width, int height);
    void shutdown();

    void render(const Camera& camera, int cursorR, int cursorC);

private:
    static GLuint compileShader(GLenum type, const char* source);

    GLuint program_ = 0;
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
};
