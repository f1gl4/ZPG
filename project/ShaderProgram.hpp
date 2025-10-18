#pragma once
#include <GL/glew.h>
#include "glm/gtc/type_ptr.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>

#include "Light.hpp"
#include "Camera.hpp"
#include "ShaderLoader.h"
#include "Observer.hpp"

class Camera;


class ShaderProgram : public Observer {
public:
    ShaderProgram(const char* vertexPath, const char* fragmentPath);

    void use() const;
    void setUniformMat4(const std::string& name, const glm::mat4& matrix) const;
    void setUniformInt(const std::string& name, int value) const;
    void setUniformBool(const std::string& name, bool value) const;
    void update() override;
    void setCamera(Camera* cam);
    void setCameraPosition(const glm::vec3& cameraPosition) const;
    void setLight(const glm::vec3& lightPosition, const glm::vec3& lightColor) const;

    void setLight(Light* lightSource) {
        light = lightSource;
        light->addObserver(this);
    }

    void setLights(const std::vector<Light*>& lights);

private:
    GLuint id_shader;
    Camera* camera;
    Light* light;
    std::vector<Light*> lights;
};
