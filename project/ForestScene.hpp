#pragma once
#include "Scene.hpp"
#include "Model.hpp"
#include "DynamicRotate.hpp"
#include "SpotlightUpdater.hpp"
#include "Skybox.hpp"

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

class ForestScene : public Scene {
public:
    ForestScene(ShaderProgram* shader);
    void initialize() override;
    GLuint loadTexture(const std::string& filePath);

    const std::vector<DrawableObject*>& getRotatingTrees() const {
        return rotatingTrees;
    }

private:
    //std::vector<Light*> lights;
    std::vector<DrawableObject*> rotatingTrees;

};
