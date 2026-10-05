#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    Shader() = default;
    ~Shader() { shutdown(); }

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    bool load(const char* vertexSrc, const char* fragmentSrc);
    void shutdown();

    void use() const;

    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

    GLuint id() const { return program_; }

private:
    static GLuint compileShader(GLenum type, const char* source);
    GLuint program_ = 0;
};
