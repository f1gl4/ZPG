#pragma once
#include "TransformationComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Rotate : public TransformationComponent 
{
private:
    float angle;
    glm::vec3 axis;
public:
    Rotate(float ang, const glm::vec3& ax) : angle(ang), axis(ax) {}
    glm::mat4 apply(const glm::mat4& model) const override {
        return glm::rotate(model, glm::radians(angle), axis);
    }

    void setAngle(float ang) {
        angle = ang;
    }
};