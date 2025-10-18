#pragma once
#include "Rotate.hpp"

class DynamicRotate : public Rotate {
private:
    float currentAngle; 
    float rotationSpeed; 

public:
    // angle and speed
    DynamicRotate(float initialAngle, float speed, const glm::vec3& axis)
        : Rotate(initialAngle, axis), currentAngle(initialAngle), rotationSpeed(speed) {}

    // update angle
    void update(float deltaTime) {
        currentAngle += rotationSpeed * deltaTime;
        setAngle(currentAngle);
    }
};
