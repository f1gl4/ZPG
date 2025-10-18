#include "SpheresScene.hpp"

#include <glm/vec3.hpp>
#include <iostream>


SpheresScene::SpheresScene(ShaderProgram* shader) : Scene(shader) {}

void SpheresScene::initialize()
{
    std::cout << "Spheres scene initialize successfully." << std::endl;

    // Initialize lighting
    auto* centralLight = new Light(
        glm::vec3(0.0f, 0.0f, 0.0f),  // centre
        glm::vec3(1.0f, 1.0f, 1.0f), // white light
        glm::vec3(0.0f, 0.0f, 0.0f), // 
        1.0f, 0.09f, 0.032f           // attent.
    );

    addLight(centralLight);


    ObjectFactory factory(shader);
    Model* sphereModel = new Model(sphere, sphereVertexCount);
    float distance = 2.0f;

    factory.addObjectToScene(this, sphereModel, glm::vec3(-distance, 0.0f, 0.0f), glm::vec3(1.0f));
    factory.addObjectToScene(this, sphereModel, glm::vec3(distance, 0.0f, 0.0f), glm::vec3(1.0f));
    factory.addObjectToScene(this, sphereModel, glm::vec3(0.0f, distance, 0.0f), glm::vec3(1.0f));
    factory.addObjectToScene(this, sphereModel, glm::vec3(0.0f, -distance, 0.0f), glm::vec3(1.0f));

    camera->setPosition(glm::vec3(0.0f, 0.0f, 6.0f));
    camera->setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
    shader->setCamera(camera);
}