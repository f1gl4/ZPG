#include "SkyboxScene.hpp"

#include "ObjectFactory.hpp"
#include "ShaderProgram.hpp"


SkyboxScene::SkyboxScene(ShaderProgram* shader) : Scene(shader) {}

void SkyboxScene::initialize() {
    std::cout << "SKYBOX scene initialize successfully." << std::endl;

    // SKYBOX
    //Shader* skyboxShader = new Shader("Shaders/Skybox.vert", "Shaders/Skybox.frag");
    std::vector<std::string> faces = {
        "Cubemap/posx.jpg", "Cubemap/negx.jpg", "Cubemap/posy.jpg",
        "Cubemap/negy.jpg", "Cubemap/posz.jpg", "Cubemap/negz.jpg"
    };
    Skybox* skybox = new Skybox(faces);
    DrawableObject* skyboxObject = new DrawableObject(skybox, shader);
    addObject(skyboxObject);

    // camera set up
    camera->setPosition(glm::vec3(0.0f, 0.0f, 5.0f));  // camera pos
    camera->setTarget(glm::vec3(0.0f, 0.0f, -1.0f));      // camera looks at
    shader->setCamera(camera);
}

