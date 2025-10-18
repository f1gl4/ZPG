#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>
#include "TexturedModel.hpp"
#include "ShaderProgram.hpp"
#include "Translate.hpp"

class Skybox {
public:
    Skybox(const std::vector<std::string>& faces);
    ~Skybox();

    void draw(ShaderProgram* shader);

private:
    GLuint cubemapTexture;
    TexturedModel* model;

    GLuint loadCubemap(const std::vector<std::string>& faces);
};
