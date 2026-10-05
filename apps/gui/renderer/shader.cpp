#include "renderer/shader.h"

#include <cstdio>

bool Shader::load(const char* vertexSrc, const char* fragmentSrc) {
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);
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
        fprintf(stderr, "Shader program link error:\n%s\n", log);
        glDeleteProgram(program_);
        program_ = 0;
        return false;
    }

    return true;
}

void Shader::shutdown() {
    if (program_) {
        glDeleteProgram(program_);
        program_ = 0;
    }
}

void Shader::use() const {
    glUseProgram(program_);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(program_, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(program_, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(program_, name.c_str()), x, y);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

GLuint Shader::compileShader(GLenum type, const char* source) {
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
