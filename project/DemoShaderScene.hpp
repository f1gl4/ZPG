#pragma once
#include "Scene.hpp"
#include "ShaderProgram.hpp"
#include "ObjectFactory.hpp"
#include "Model.hpp"

class DemoShaderScene : public Scene {
public:
    DemoShaderScene();
    void initialize() override;
private:
    ShaderProgram* constantShader;
    ShaderProgram* lambertShader;
    ShaderProgram* phongShader;
    ShaderProgram* blinnShader;
};
