#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera() {
        updateProjection(1280, 720);
        view_ = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 10.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
    }

    // projection matrix
    void updateProjection(int width, int height) {
        width_ = width > 0 ? width : 1;
        height_ = height > 0 ? height : 1;
        float aspect = static_cast<float>(width_) / static_cast<float>(height_);

        float orthoSize = 10.0f;
        float left = -orthoSize * 0.5f * aspect;
        float right = orthoSize * 0.5f * aspect;
        float bottom = -orthoSize * 0.5f;
        float top = orthoSize * 0.5f;

        projection_ = glm::ortho(left, right, bottom, top, 0.1f, 100.0f);
    }

    glm::mat4 projectionMatrix() const { return projection_; }
    glm::mat4 viewMatrix() const { return view_; }
    glm::mat4 viewProjectionMatrix() const { return projection_ * view_; }

private:
    int width_ = 1280;
    int height_ = 720;
    glm::mat4 projection_;
    glm::mat4 view_;
};
