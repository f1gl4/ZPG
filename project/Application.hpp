//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>

// Include .hpp files
#include "ShaderProgram.hpp"
#include "Model.hpp"
#include "Figure.hpp"
#include "DrawableObject.hpp"
#include "Scene.hpp"
#include "ObjectFactory.hpp"
#include "Camera.hpp"
#include "ForestScene.hpp"
#include "BasicScene.hpp"
#include "SpheresScene.hpp"
#include "DemoShaderScene.hpp"
#include "DynamicRotate.hpp"
#include "SkyboxScene.hpp"

class Application
{
public:
	GLFWwindow* window;

	void run();
	void destroy();
	//void initialize();
	void createWindow();

	void createShaders();
	void createModels();
	void createScenes();

	//void setActiveScene(int index);
	Scene* getCurrentScene() { return currentScene; }
	Camera* getCamera() const { return camera; }
	void setCamera(Camera* cam) { camera = cam; };

	void updateTreeRotations(float deltaTime);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

private:
	ShaderProgram* shaderPurple;
	ShaderProgram* shaderGreen;

	Camera* camera;

	std::vector<DrawableObject*> drawableObjects;
	std::vector<Model*> models;
	std::vector<Figure*> figures;
	std::vector<ShaderProgram*> shaders;
	std::vector<Scene*> scenes;

	int currentSceneIndex = 0;
	Scene* currentScene;
	float deltaTime = 0.0f;
	void switchScene();


	void printVersionInfo();
	static void error_callback(int error, const char* description);

};