#include "Camera.hpp"
#include <GLFW/glfw3.h>

Camera::Camera() : front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
yaw(-90.0f), pitch(0.0f), speed(3.0f), sensitivity(0.1f), position(glm::vec3(0.0f, 0.0f, 3.0f)) {
    updateCameraVectors();
    updateViewMatrix();
    updateProjectionMatrix();
}

void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
    updateViewMatrix();
    notifyObservers(); //
}

void Camera::setTarget(const glm::vec3& targ) {
    target = targ;
    updateViewMatrix();
    notifyObservers(); //
}

void Camera::processKeyboardInput(int key, float deltaTime) {
    float velocity = speed * deltaTime;
    if (key == GLFW_KEY_W) position += glm::normalize(glm::vec3(front.x, 0.0f, front.z)) * velocity;
    if (key == GLFW_KEY_S) position -= glm::normalize(glm::vec3(front.x, 0.0f, front.z)) * velocity;
    if (key == GLFW_KEY_A) position -= glm::normalize(glm::vec3(right.x, 0.0f, right.z)) * velocity;
    if (key == GLFW_KEY_D) position += glm::normalize(glm::vec3(right.x, 0.0f, right.z)) * velocity;

    updateViewMatrix();
    notifyObservers(); //
}

void Camera::processMouseMovement(float xOffset, float yOffset) {
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
    updateViewMatrix();
    notifyObservers(); //
}

void Camera::updateCameraVectors() {
    glm::vec3 frontVector;
    frontVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontVector.y = sin(glm::radians(pitch));
    frontVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frontVector);
    right = glm::normalize(glm::cross(front, up));
}

const glm::mat4& Camera::getViewMatrix() const {
    return viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

const glm::vec3& Camera::getPosition() const {
    return position;
}

const glm::vec3& Camera::getFront() const {
    return front;
}


void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(position, position + front, up);
}

void Camera::updateProjectionMatrix() {
    projectionMatrix = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}
