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

// Include .hpp files
#include "Application.hpp"



int main() {
    Application app;
    app.createWindow();
    app.createScenes();

    glfwSetKeyCallback(app.window, Application::key_callback);
    glfwSetWindowUserPointer(app.window, &app); // app pointer

    app.run();
    app.destroy();
    return 0;
}