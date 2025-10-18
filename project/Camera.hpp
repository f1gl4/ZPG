#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Subject.hpp"

class Camera : public Subject {
public:
    Camera();

    void setPosition(const glm::vec3& position);
    void setTarget(const glm::vec3& target);

    const glm::mat4& getViewMatrix() const;
    const glm::mat4& getProjectionMatrix() const;
    const glm::vec3& getPosition() const;
    const glm::vec3& getFront() const;


    void processKeyboardInput(int key, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset);

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 front;

    float yaw;
    float pitch;
    float speed;
    float sensitivity;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    void updateViewMatrix();
    void updateProjectionMatrix();
    void updateCameraVectors();
};
