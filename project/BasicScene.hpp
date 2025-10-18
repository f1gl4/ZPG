#pragma once
#include "Scene.hpp"

class BasicScene : public Scene {
public:
    BasicScene(ShaderProgram* shader);
    void initialize() override;
};
