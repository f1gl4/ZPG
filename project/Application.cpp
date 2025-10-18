#include "Application.hpp"


#include <cstdlib> 

// for mouse position
double lastX = 400, lastY = 300;
bool firstMouse = true;

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (app && app->getCamera())
	{
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		{
			app->switchScene();
		}

		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			app->getCamera()->processKeyboardInput(key, app->deltaTime);
		}

	}
}

void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = static_cast<float>(xpos - lastX);
	float yOffset = static_cast<float>(lastY - ypos);
	lastX = xpos;
	lastY = ypos;

	if (app && app->getCamera())
	{
		app->getCamera()->processMouseMovement(xOffset, yOffset);
	}
}

void Application::createWindow()
{
	//GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}


	this->window = glfwCreateWindow(1200, 800, "ZPG", NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	this->printVersionInfo();

	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	glViewport(0, 0, width, height);

	glfwSetWindowUserPointer(this->window, this);
	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Application::printVersionInfo()
{
	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}


void Application::createScenes() {
	ShaderProgram* skyboxShader = new ShaderProgram("Shaders/Skybox.vert", "Shaders/Skybox.frag");
	auto* skyboxScene = new SkyboxScene(skyboxShader);
	skyboxScene->initialize();
	skyboxScene->getCamera()->addObserver(skyboxShader);

	ShaderProgram* forestShader = new ShaderProgram("Shaders/Phong.vert", "Shaders/Phong.frag");
	auto* forestScene = new ForestScene(forestShader);
	forestScene->initialize();
	forestScene->getCamera()->addObserver(forestShader);

	ShaderProgram* basicShader = new ShaderProgram("Shaders/PhongSimple.vert", "Shaders/PhongSimple.frag");
	auto* basicScene = new BasicScene(basicShader);
	basicScene->initialize();
	basicScene->getCamera()->addObserver(basicShader);

	ShaderProgram* phongShader = new ShaderProgram("Shaders/Phong.vert", "Shaders/Phong.frag");
	auto* spheresScene = new SpheresScene(phongShader);
	spheresScene->initialize();
	spheresScene->getCamera()->addObserver(phongShader);

	scenes.push_back(skyboxScene);
	scenes.push_back(forestScene);
	scenes.push_back(basicScene);
	scenes.push_back(spheresScene);


	if (!scenes.empty()) {
		currentSceneIndex = 0;
		currentScene = scenes[currentSceneIndex];
		camera = currentScene->getCamera();
	}
}

void Application::updateTreeRotations(float deltaTime) {
	// FOR FORESTSCENE ONLY
	auto* forestScene = dynamic_cast<ForestScene*>(currentScene);
	if (forestScene) {
		// with get trees in ForestScene
		for (auto* tree : forestScene->getRotatingTrees()) {
			CompositeTransformation* transformation = tree->getTransformation();
			//transformation->addTransformation(new Rotate(deltaTime * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
			for (auto* component : transformation->getTransformations()) {
				auto* dynamicRotate = dynamic_cast<DynamicRotate*>(component);
				if (dynamicRotate)
				{
					dynamicRotate->update(deltaTime);
				}
			}
		}
	}
}

void Application::run()
{

	glfwSetCursorPosCallback(this->window, mouse_callback);
	glfwSetKeyCallback(this->window, key_callback);

	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(this->window)) {

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (dynamic_cast<ForestScene*>(currentScene)) {
			updateTreeRotations(deltaTime);
		}

		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scenes[currentSceneIndex]->render();

		// update other events like input handling
		glfwPollEvents();

		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->window);
	}
}

void Application::switchScene() {
	currentSceneIndex = (currentSceneIndex + 1) % scenes.size();
	currentScene = scenes[currentSceneIndex];
	camera = currentScene->getCamera();
	//camera->notifyShader();
	std::cout << "Scene switches successfully." << std::endl;
}

void Application::destroy()
{
	for (auto model : models) delete model;
	for (auto figure : figures) delete figure;
	for (auto shader : shaders) delete shader;
	for (auto object : drawableObjects) delete object;
	for (auto scene : scenes) delete scene;

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}