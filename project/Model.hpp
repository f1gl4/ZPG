#include <GL/glew.h>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

#pragma once

class Model
{
public:
    // constructor, receive array of vertices (points) and its size
    Model(float* vertices, size_t vertexCount);

    ~Model();

    // draw model
    void draw();

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    size_t vertexCount;  // count of vertices
};
