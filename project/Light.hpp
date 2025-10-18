#pragma once

#include <glm/glm.hpp>
#include "Subject.hpp"

class Light : public Subject {
public:
    Light(const glm::vec3& position, const glm::vec3& color,
        const glm::vec3& direction = glm::vec3(0.0f),
        float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f,
        float cutoff = 0.0f, float outerCutoff = 0.0f)
        : position(position), color(color), direction(direction),
        constant(constant), linear(linear), quadratic(quadratic),
        cutoff(cutoff), outerCutoff(outerCutoff) {}

    const glm::vec3& getPosition() const { return position; }
    const glm::vec3& getColor() const { return color; }
    const glm::vec3& getDirection() const { return direction; }

    float getConstant() const { return constant; }
    float getLinear() const { return linear; }
    float getQuadratic() const { return quadratic; }
    float getCutoff() const { return cutoff; }
    float getOuterCutoff() const { return outerCutoff; }

    void setPosition(const glm::vec3& newPosition) {
        position = newPosition;
        notifyObservers();
    }

    void setDirection(const glm::vec3& newDirection) {
        direction = newDirection;
        notifyObservers();
    }

    void setCutoff(float newCutoff) {
        cutoff = newCutoff;
        notifyObservers();
    }

    void setColor(const glm::vec3& newColor) {
        color = newColor;
        notifyObservers();
    }

private:
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 direction;
    float constant;
    float linear;
    float quadratic;
    float cutoff;
    float outerCutoff;
};
