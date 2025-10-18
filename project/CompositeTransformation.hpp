#pragma once
#include "TransformationComponent.hpp"
#include "Translate.hpp"
#include "Rotate.hpp"
#include "Scale.hpp"

#include <vector>
#include <memory>

class CompositeTransformation : public TransformationComponent {
private:
    std::vector<TransformationComponent*> transformations;
    float rotationAngle = 0.0f;

public:
    ~CompositeTransformation() {
        for (auto* transformation : transformations) {
            delete transformation;
        }
    }

    void addTransformation(TransformationComponent* transformation) {
        transformations.push_back(transformation);
    }

    const std::vector<TransformationComponent*>& getTransformations() const {
        return transformations;
    }

    void setRotationAngle(float angle)
    {
        rotationAngle = angle;
    }

    glm::mat4 apply(const glm::mat4& model) const override {
        glm::mat4 result = model;
        for (const auto* transformation : transformations) {
            result = transformation->apply(result);
        }
        result = glm::rotate(result, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        return result;
    }
};