#include "DemoShaderScene.hpp"

#include <glm/vec3.hpp>
#include <iostream>


DemoShaderScene::DemoShaderScene()
    : constantShader(nullptr), lambertShader(nullptr), phongShader(nullptr), blinnShader(nullptr) {}

void DemoShaderScene::initialize()
{
    std::cout << "Demo shader scene initialize successfully." << std::endl;

    constantShader = new ShaderProgram("Shaders/Color.vert", "Shaders/Color.frag");
    lambertShader = new ShaderProgram("Shaders/Lambert.vert", "Shaders/Lambert.frag");
    phongShader = new ShaderProgram("Shaders/PhongSimple.vert", "Shaders/PhongSimple.frag");
    blinnShader = new ShaderProgram("Shaders/Blinn.vert", "Shaders/Blinn.frag");

    auto* light = new Light(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f)); // white
    //constantShader->setLight(light);
    lambertShader->setLight(light);
    phongShader->setLight(light);
    blinnShader->setLight(light);

    // object factory
    ObjectFactory factory(constantShader);

    // initialize models
    Model* treeModel = new Model(tree, treeVertexCount);
    Model* bushModel = new Model(bushes, bushesVertexCount);
    Model* giftModel = new Model(gift, giftVertexCount);
    Model* sphereModel = new Model(sphere, sphereVertexCount);

    // add objects with different shaders

    // tree with constant shader
    factory = ObjectFactory(constantShader);  //
    factory.addObjectToScene(this, treeModel, glm::vec3(-3.0f, 0.0f, -3.0f), glm::vec3(1.0f));

    // bushes with lambert shader
    factory = ObjectFactory(lambertShader);
    factory.addObjectToScene(this, bushModel, glm::vec3(3.0f, 0.0f, -3.0f), glm::vec3(1.0f));

    // gift with phong shader
    factory = ObjectFactory(phongShader);
    factory.addObjectToScene(this, giftModel, glm::vec3(-3.0f, 0.0f, 3.0f), glm::vec3(1.0f));

    // sphere with blinn shader
    factory = ObjectFactory(blinnShader);
    factory.addObjectToScene(this, sphereModel, glm::vec3(3.0f, 0.0f, 3.0f), glm::vec3(1.0f));

    // camera set up
    camera->setPosition(glm::vec3(0.0f, 2.0f, 10.0f));
    camera->setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
    constantShader->setCamera(camera);  //
    lambertShader->setCamera(camera);
    phongShader->setCamera(camera);
    blinnShader->setCamera(camera);
}