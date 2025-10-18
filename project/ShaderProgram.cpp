#include "ShaderProgram.hpp"


ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath) {

    ShaderLoader loader(vertexPath, fragmentPath, &id_shader);
    camera = nullptr;
}


void ShaderProgram::use() const {
    glUseProgram(id_shader);
}


void ShaderProgram::setUniformMat4(const std::string& name, const glm::mat4& matrix) const
{
    GLuint loc = glGetUniformLocation(id_shader, name.c_str());
    if (loc != -1)
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    else {
        std::cerr << "Uniform loc cannot found for " << name << std::endl;
    }
}

void ShaderProgram::setUniformInt(const std::string& name, int value) const {
    GLuint loc = glGetUniformLocation(id_shader, name.c_str());
    if (loc != -1) {
        glUniform1i(loc, value);
    }
    else {
        std::cerr << "Uniform loc not found for " << name << std::endl;
    }
}

void ShaderProgram::setUniformBool(const std::string& name, bool value) const {
    GLuint loc = glGetUniformLocation(id_shader, name.c_str());
    if (loc != -1) {
        glUniform1i(loc, value ? 1 : 0);
    }
    else {
        std::cerr << "Uniform loc not found for " << name << std::endl;
    }
}



void ShaderProgram::setCameraPosition(const glm::vec3& cameraPosition) const {
    GLuint loc = glGetUniformLocation(id_shader, "cameraPosition");
    if (loc != -1) {
        glUniform3fv(loc, 1, glm::value_ptr(cameraPosition));
    }
}


void ShaderProgram::setLight(const glm::vec3& lightPosition, const glm::vec3& lightColor) const {
    GLuint posLoc = glGetUniformLocation(id_shader, "lightPosition");
    GLuint colorLoc = glGetUniformLocation(id_shader, "lightColor");
    if (posLoc != -1 && colorLoc != -1) {
        glUniform3fv(posLoc, 1, glm::value_ptr(lightPosition));
        glUniform3fv(colorLoc, 1, glm::value_ptr(lightColor));
    }
    else {
        std::cerr << "Failed to find light uniform locations." << std::endl;
    }
}


void ShaderProgram::setLights(const std::vector<Light*>& lights) {
    use();
    for (size_t i = 0; i < lights.size(); ++i) {
        std::string base = "lights[" + std::to_string(i) + "]";
        GLuint posLoc = glGetUniformLocation(id_shader, (base + ".position").c_str());
        GLuint dirLoc = glGetUniformLocation(id_shader, (base + ".direction").c_str());
        GLuint colorLoc = glGetUniformLocation(id_shader, (base + ".color").c_str());
        GLuint constLoc = glGetUniformLocation(id_shader, (base + ".constant").c_str());
        GLuint linearLoc = glGetUniformLocation(id_shader, (base + ".linear").c_str());
        GLuint quadLoc = glGetUniformLocation(id_shader, (base + ".quadratic").c_str());
        GLuint cutoffLoc = glGetUniformLocation(id_shader, (base + ".cutoff").c_str());
        GLuint outerCutoffLoc = glGetUniformLocation(id_shader, (base + ".outerCutoff").c_str());

        if (posLoc != -1) glUniform3fv(posLoc, 1, glm::value_ptr(lights[i]->getPosition()));
        if (dirLoc != -1) glUniform3fv(dirLoc, 1, glm::value_ptr(lights[i]->getDirection()));
        if (colorLoc != -1) glUniform3fv(colorLoc, 1, glm::value_ptr(lights[i]->getColor()));
        if (constLoc != -1) glUniform1f(constLoc, lights[i]->getConstant());
        if (linearLoc != -1) glUniform1f(linearLoc, lights[i]->getLinear());
        if (quadLoc != -1) glUniform1f(quadLoc, lights[i]->getQuadratic());
        if (cutoffLoc != -1) glUniform1f(cutoffLoc, lights[i]->getCutoff());
        if (outerCutoffLoc != -1) glUniform1f(outerCutoffLoc, lights[i]->getOuterCutoff());
    }
    glUniform1i(glGetUniformLocation(id_shader, "numberOfLights"), lights.size());
}



void ShaderProgram::update() {
    use();
    if (camera) {
        setUniformMat4("view", camera->getViewMatrix());
        setUniformMat4("projection", camera->getProjectionMatrix());
        setCameraPosition(camera->getPosition());
    }
    if (light) {
        setLight(light->getPosition(), light->getColor());
    }
}


void ShaderProgram::setCamera(Camera* cam)
{
    camera = cam;
    camera->addObserver(this);
}