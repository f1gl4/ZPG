#pragma once
#include "TransformationComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Translate : public TransformationComponent 
{
private:
    glm::vec3 position;
public:
    explicit Translate(const glm::vec3& pos) : position(pos) {}
    glm::mat4 apply(const glm::mat4& model) const override {
        return glm::translate(model, position);
    }
};