#pragma once
#include <glm/glm.hpp>

class TransformationComponent 
{
public:
    virtual ~TransformationComponent() = default;
    virtual glm::mat4 apply(const glm::mat4& model) const = 0;
};