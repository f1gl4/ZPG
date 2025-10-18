#pragma once
#include "Scene.hpp"
#include "ShaderProgram.hpp"
#include "ObjectFactory.hpp"
#include "Model.hpp"

class SpheresScene : public Scene {
public:
    SpheresScene(ShaderProgram* shader);
    void initialize() override;
};
