#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ShaderProgram.hpp"
#include "Mesh.hpp"

class AssimpModel {
public:
    AssimpModel(const std::string& path);
    void draw(ShaderProgram* shader, GLuint textureID = 0, bool useTexture = false) const;

private:
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    unsigned int loadMaterialTexture(aiMaterial* mat, aiTextureType type);
};
