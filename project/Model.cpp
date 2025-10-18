#include "Model.hpp"


Model::Model(float* vertices, size_t vertexCount) : vertexCount(vertexCount) {
    // Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO

    // Vertex buffer object (VBO)
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);  // enable vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);

    glEnableVertexAttribArray(1);  // 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


Model::~Model() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}


void Model::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount / 6);  // 3 for vertex 3 for normal
    //glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
    glBindVertexArray(0);
}
