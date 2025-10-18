#pragma once
#include "Scene.hpp"
#include "Model.hpp"
#include "DynamicRotate.hpp"
#include "SpotlightUpdater.hpp"
#include "Skybox.hpp"

class SkyboxScene : public Scene {
public:
    SkyboxScene(ShaderProgram* shader);
    void initialize() override;

    const std::vector<DrawableObject*>& getRotatingTrees() const {
        return rotatingTrees;
    }


private:
    //std::vector<Light*> lights;
    std::vector<DrawableObject*> rotatingTrees;
  
};
