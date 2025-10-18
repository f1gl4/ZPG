#pragma once
#include "ShaderProgram.hpp"
#include "Model.hpp"
#include "Figure.hpp"
#include "CompositeTransformation.hpp"
#include "Skybox.hpp"
#include "AssimpModel.hpp"
#include <memory>
#include <glm/glm.hpp>

class DrawableObject {
public:
    DrawableObject(Model* model, ShaderProgram* shader)
        : model(model), shader(shader), transformation(new CompositeTransformation()) {}

    DrawableObject(Figure* figure, ShaderProgram* shader)
        : model(nullptr), figure(figure), shader(shader), transformation(new CompositeTransformation()) {}

    DrawableObject(Skybox* skybox, ShaderProgram* shader)
        : model(nullptr), figure(nullptr), skybox(skybox), shader(shader), transformation(nullptr) {}

    DrawableObject(AssimpModel* assimpModel, ShaderProgram* shader, GLuint textureID)
        : model(nullptr), assimpModel(assimpModel), figure(nullptr), skybox(nullptr), shader(shader),
        textureID(textureID), transformation(new CompositeTransformation()) {}

    DrawableObject(TexturedModel* texturedModel, ShaderProgram* shader, GLuint textureID)
        : model(nullptr), assimpModel(nullptr), figure(nullptr), skybox(nullptr), texturedModel(texturedModel),
        shader(shader), textureID(textureID), transformation(new CompositeTransformation()) {}

    ~DrawableObject() {
        delete transformation;
        if (!model && figure) delete figure;
    }

    void draw() const {
        shader->use();

        if (skybox) {
            skybox->draw(shader);
        }
        else {
            glm::mat4 modelMatrix = transformation->apply(glm::mat4(1.0f));
            shader->setUniformMat4("modelMatrix", modelMatrix);
            shader->setUniformBool("useTexture", useTextureFlag);

            // bind texture
            if (useTextureFlag && textureID) {
                glActiveTexture(GL_TEXTURE0 + textureUnit);
                glBindTexture(GL_TEXTURE_2D, textureID);
                shader->setUniformInt("textureUnitID", textureUnit);
            }

            if (model) {
                model->draw();
            }
            else if (assimpModel)
            {
                assimpModel->draw(shader, textureID, useTextureFlag);
            }
            else if (texturedModel) {
                texturedModel->draw();
            }
            else if (figure) {
                figure->draw();
            }
        }

        glUseProgram(0);
    }


    void setTransformation(CompositeTransformation* transform) {
        delete transformation;
        transformation = transform;
    }

    void setTextureUnit(int unit)
    {
        textureUnit = unit;
    }

    void setUseTexture(bool useTexture)
    {
        useTextureFlag = useTexture;
    }

    CompositeTransformation* getTransformation() const { return transformation; }


private:
    Model* model = nullptr;
    AssimpModel* assimpModel = nullptr;
    TexturedModel* texturedModel = nullptr;
    Figure* figure = nullptr;
    Skybox* skybox = nullptr;
    ShaderProgram* shader = nullptr;
    CompositeTransformation* transformation;

    GLuint textureID = 0;
    int textureUnit = 0;
    bool useTextureFlag = false;
};
