#include "renderer/board_renderer.h"

#include <array>
#include <cstdio>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        color = vec4(0.87f, 0.72f, 0.53f, 1.0f);
    } else {
        color = vec4(0.42f, 0.30f, 0.20f, 1.0f);
    }
    FragColor = color;
}
)";

}  // namespace

GLuint BoardRenderer::compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        fprintf(stderr, "Shader compile error:\n%s\n", log);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

bool BoardRenderer::init(int /*width*/, int /*height*/) {
    GLuint vs = compileShader(GL_VERTEX_SHADER, kVertexSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, kFragmentSrc);
    if (!vs || !fs) return false;

    program_ = glCreateProgram();
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);
    glLinkProgram(program_);
    glDeleteShader(vs);
    glDeleteShader(fs);

    GLint ok = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(program_, sizeof(log), nullptr, log);
        fprintf(stderr, "Program link error:\n%s\n", log);
        glDeleteProgram(program_);
        return false;
    }

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
    if (program_) glDeleteProgram(program_);
    vao_ = vbo_ = program_ = 0;
}

void BoardRenderer::render(const Camera& camera, int cursorR, int cursorC) {
    glUseProgram(program_);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(8.0f, 8.0f, 1.0f));
    // create the mvp matrix
    glm::mat4 mvp = camera.viewProjectionMatrix() * model;

    GLint uMVPLoc = glGetUniformLocation(program_, "uMVP");
    GLint uCursorRLoc = glGetUniformLocation(program_, "uCursorR");
    GLint uCursorCLoc = glGetUniformLocation(program_, "uCursorC");

    glUniformMatrix4fv(uMVPLoc, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniform1i(uCursorRLoc, cursorR);
    glUniform1i(uCursorCLoc, cursorC);

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
