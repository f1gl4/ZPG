#include "Scene.hpp"

Scene::~Scene() {
    for (auto* object : objects) {
        delete object;
    }
}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::setCamera(Camera* cam) {
    camera = cam;
}

Camera* Scene::getCamera() const {
    return camera;
}

void Scene::render() const {
    //shader->update();
    shader->setLights(lights);
    camera->notifyObservers();
    for (const auto* object : objects) {
        object->draw();
    }
}
