#pragma once

#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

class TexturedModel {
public:
    // Constructor, with uv
    TexturedModel(float* vertices, size_t vertexCount);

    ~TexturedModel();

    void draw();
    void setTexture(GLuint id) { textureID = id; }

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    size_t vertexCount;
    GLuint textureID;
};
