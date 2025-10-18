#include "BasicScene.hpp"
#include "Light.hpp"

#include <GL/glew.h>
#include <iostream>

BasicScene::BasicScene(ShaderProgram* shader) : Scene(shader) {}

void BasicScene::initialize() {
    std::cout << "Initializing Basic Scene with a single triangle." << std::endl;

    // Initialize lighting
    auto* light = new Light(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    shader->setLight(light);

    float triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    Figure* triangleFigure = new Figure(triangleVertices, sizeof(triangleVertices) / sizeof(float));
    DrawableObject* triangleObject = new DrawableObject(triangleFigure, shader);
    addObject(triangleObject);


    // camera set up
    camera->setPosition(glm::vec3(0.0f, 0.0f, 2.0f));  // camera's place
    camera->setTarget(glm::vec3(0.0f, 0.0f, -1.0f));      // camera looks at
    shader->setCamera(camera);
}
