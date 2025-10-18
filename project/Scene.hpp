#pragma once

#include <vector>
#include "Camera.hpp"
#include "DrawableObject.hpp"
#include "Light.hpp"
#include <GL/glew.h>

#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/sphere.h"
#include "Models/gift.h"
#include "Models/plain.h"

class Scene {
protected:
    Camera* camera;
    ShaderProgram* shader;
    std::vector<DrawableObject*> objects;
    std::vector<Light*> lights;

public:
    Scene() : camera(new Camera()) {}
    Scene(ShaderProgram* shader) : shader(shader), camera(new Camera()) {}
    virtual ~Scene();

    void addObject(DrawableObject* object);
    void setCamera(Camera* cam); 
    Camera* getCamera() const;

    void addLight(Light* light) { lights.push_back(light); }
    const std::vector<Light*>& getLights() const { return lights; }

    virtual void initialize() = 0;
    virtual void render() const; 
};
