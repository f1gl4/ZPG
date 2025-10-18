#pragma once
#include "TransformationComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Scale : public TransformationComponent 
{
private:
    glm::vec3 scaleFactor;
public:
    explicit Scale(const glm::vec3& scale) : scaleFactor(scale) {}
    glm::mat4 apply(const glm::mat4& model) const override {
        return glm::scale(model, scaleFactor);
    }
};