#include "ForestScene.hpp"
#include <SOIL.h>
#include "ObjectFactory.hpp"
#include "ShaderProgram.hpp"


ForestScene::ForestScene(ShaderProgram* shader) : Scene(shader) {}


GLuint ForestScene::loadTexture(const std::string& filePath) {
    std::cout << "Loading texture from path: " << filePath << std::endl;

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, channels;
    unsigned char* data = SOIL_load_image(filePath.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
    if (!data) {
        std::cerr << "SOIL failed to load image: " << filePath << std::endl;
        return 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}



void ForestScene::initialize() {
    std::cout << "Forest scene initialize successfully." << std::endl;


    // 4 lights
    auto* light1 = new Light(
        glm::vec3(25.0f, 0.0f, 20.0f),  // Position
        glm::vec3(1.0f, 0.5f, 0.5f),   // Color
        glm::vec3(0.0f),               // Direction 
        0.1f,                          // Constant
        0.7f,                          // Linear
        0.017f                         // Quadratic
    ); // Red

    auto* light2 = new Light(
        glm::vec3(25.0f, 0.0f, 1.0f),  // Position
        glm::vec3(0.5f, 1.0f, 0.5f),   // Color
        glm::vec3(0.0f),               // Direction
        0.5f,                          // Constant
        0.07f,                         // Linear
        0.017f                         // Quadratic
    ); // Green

    auto* light3 = new Light(
        glm::vec3(0.0f, 0.0f, 25.0f),
        glm::vec3(0.5f, 0.5f, 1.0f),
        glm::vec3(0.0f), // Direction
        0.5f,
        0.09f,
        0.032f
    ); // Blue

    auto* light4 = new Light(
        glm::vec3(2.0f, 26.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 0.5f),
        glm::vec3(0.0f), // Direction
        1.0f,
        0.01f,
        0.9f
    ); // Yellow

    addLight(light1);
    addLight(light2);
    addLight(light3);
    addLight(light4);

    // Spotlight tied to camera
    auto* spotlight = new Light(
        camera->getPosition(),  // camera pos
        glm::vec3(1.0f, 1.0f, 1.0f), // white light
        glm::normalize(camera->getFront()), // camera direction
        1.0f, 0.09f, 0.032f, // attent.light
        glm::cos(glm::radians(12.5f)), // cutoff
        glm::cos(glm::radians(17.5f))  // outerCutoff
    );
    camera->addObserver(new SpotlightUpdater(camera, spotlight)); // observer for spotlight, use SpotlightUpdater
    addLight(spotlight);

    ObjectFactory factory(shader);

    // .OBJ
    auto* houseModel = new AssimpModel("Models/house.obj");
    auto* loginModel = new AssimpModel("Models/login.obj");
    auto* zombieModel = new AssimpModel("Models/zombie.obj");
    auto* plainModel = new AssimpModel("Models/plain.obj");

    // Models
    Model* treeModel = new Model(tree, treeVertexCount);
    Model* bushModel = new Model(bushes, bushesVertexCount);
    Model* sphereModel = new Model(sphere, sphereVertexCount);
    auto* grassModel = new TexturedModel(plain, plainVertexCount);
    Model* giftModel = new Model(gift, giftVertexCount);

    // Textures
    GLuint grassTexture = loadTexture("Cubemap/grass.png");
    GLuint woodTexture = loadTexture("Cubemap/wooden_fence.png");
    GLuint houseTexture = loadTexture("Cubemap/house.png");
    GLuint zombieTexture = loadTexture("Cubemap/zombie.png");


    factory.addObjectToScene(this, houseModel, glm::vec3(10.0f, 0.0f, 30.0f), glm::vec3(1.0f), houseTexture, true);
    factory.addObjectToScene(this, loginModel, glm::vec3(10.0f, 0.0f, 15.0f), glm::vec3(1.0f), woodTexture, true);
    factory.addObjectToScene(this, zombieModel, glm::vec3(8.0f, 0.0f, 18.2f), glm::vec3(1.0f), zombieTexture, true);
    factory.addObjectToScene(this, plainModel, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f), grassTexture, true);

    factory.addRandomObjectsToScene(this, treeModel, 75, 50.0f);
    factory.addRandomObjectsToScene(this, bushModel, 250, 50.0f);
    factory.addObjectToScene(this, sphereModel, glm::vec3(2.0f, 30.0f, 1.0f), glm::vec3(3.0f));
    factory.addObjectToScene(this, giftModel, glm::vec3(14.0f, 0.0f, 15.0f), glm::vec3(1.0f));

    // ADD TREE ROTATING
    glm::vec3 rotatingTreePosition(2.0f, 0.0f, 0.0f);
    for (int i = 0; i < 3; i++) {
        CompositeTransformation* rotatingTransformation = new CompositeTransformation();
        rotatingTransformation->addTransformation(new Translate(rotatingTreePosition));
        rotatingTransformation->addTransformation(new Scale(glm::vec3(1.0f)));

        // make object TREE rotating
        DynamicRotate* dynamicRotation = new DynamicRotate(0.0f, 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        rotatingTransformation->addTransformation(dynamicRotation);

        DrawableObject* rotatingTree = new DrawableObject(treeModel, shader);
        rotatingTree->setTransformation(rotatingTransformation);
        rotatingTrees.push_back(rotatingTree); // push to vector
        addObject(rotatingTree);

        // pos by x
        rotatingTreePosition.x += 5.0f;
        //rotatingTreePosition.z += 2.0f;
    }


    // camera set up
    camera->setPosition(glm::vec3(10.0f, 1.0f, 20.0f));  // camera pos
    camera->setTarget(glm::vec3(0.0f, 0.0f, 0.0f));      // camera looks at
    shader->setCamera(camera);
}
