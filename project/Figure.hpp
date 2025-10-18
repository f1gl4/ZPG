#include <GL/glew.h>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

#pragma once

class Figure
{
public:
    // constructor, receive array of vertices (points) and its size
    Figure(float* vertices, size_t vertexCount);

    ~Figure();

    // draw figure
    void draw();

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    size_t vertexCount;  // count of vertices
};
