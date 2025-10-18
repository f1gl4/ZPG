#pragma once

#include "Scene.hpp"
#include "DrawableObject.hpp"
#include "CompositeTransformation.hpp"

#include <glm/glm.hpp>
#include <cstdlib>
#include <memory>

class ObjectFactory {
private:
    ShaderProgram* shader;

public:
    explicit ObjectFactory(ShaderProgram* shader) : shader(shader) {}

    void addObjectToScene(Scene* scene, AssimpModel* assimpModel, const glm::vec3& position, const glm::vec3& scale, GLuint textureID, bool useTexture) {
        auto* transformation = new CompositeTransformation();
        transformation->addTransformation(new Translate(position));
        transformation->addTransformation(new Scale(scale));

        auto* object = new DrawableObject(assimpModel, shader, textureID);
        object->setTransformation(transformation);
        object->setUseTexture(useTexture);
        object->setTextureUnit(0);
        scene->addObject(object);
    }

    void addObjectToScene(Scene* scene, TexturedModel* texturedModel, const glm::vec3& position, const glm::vec3& scale, GLuint textureID, int textureUnit, bool useTexture) {
        auto* transformation = new CompositeTransformation();
        transformation->addTransformation(new Translate(position));
        transformation->addTransformation(new Scale(scale));

        auto* object = new DrawableObject(texturedModel, shader, textureID);
        object->setTransformation(transformation);
        object->setTextureUnit(textureUnit);
        object->setUseTexture(useTexture);
        scene->addObject(object);
    }

    void addObjectToScene(Scene* scene, Model* model, const glm::vec3& position, const glm::vec3& scale) {
        CompositeTransformation* transformation = new CompositeTransformation();
        transformation->addTransformation(new Translate(position));
        transformation->addTransformation(new Scale(scale));

        DrawableObject* object = new DrawableObject(model, shader);
        object->setTransformation(transformation);
        scene->addObject(object);
    }

    void addRandomObjectsToScene(Scene* scene, Model* model, int count, float areaSize) {
        for (int i = 0; i < count; ++i) {
            glm::vec3 randomPosition(
                static_cast<float>(rand()) / RAND_MAX * areaSize - areaSize / 2,
                0.0f,
                static_cast<float>(rand()) / RAND_MAX * areaSize - areaSize / 2
            );
            glm::vec3 randomScale((rand() % 2 + 1) * 0.5f);
            addObjectToScene(scene, model, randomPosition, randomScale);
        }
    }
};

// in ObjectFactory we have functions for adding objects into scenes. Make DrawableObject object -> addObject to scene. 
// in Application.cpp run() calls scenes[]->render(). in Scene::render() object->draw()