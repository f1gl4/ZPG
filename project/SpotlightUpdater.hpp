#pragma once

#include "Observer.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class SpotlightUpdater : public Observer {
private:
    Camera* camera;
    Light* spotlight;

public:
    SpotlightUpdater(Camera* cam, Light* spot) : camera(cam), spotlight(spot) {}

    void update() override {
        spotlight->setPosition(camera->getPosition());
        spotlight->setDirection(camera->getFront());
    }

};
