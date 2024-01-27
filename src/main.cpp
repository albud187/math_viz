#include <iostream>
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "rendering/shader.h"
#include "programs/rectangle.hpp"
std::string Shader::defaultDirectory = "/home/alfab/experiments/math_viz/src/assets/shaders";

// initialization methods
void initGLFW(unsigned int versionMajor, unsigned int versionMinor);

void createWindow(GLFWwindow*& window,
	const char* title, unsigned int width, unsigned int height,
	GLFWframebuffersizefun framebufferSizeCallback);

// callback signatures
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

void processInput();
//void updateCameraMatrices();

// GLOBALS
int scr_width = 800, scr_height = 800;
GLFWwindow* window = nullptr;

//GLOBAL PROGRAMS
Rectangle rect;

//MAIN
int main() {
    std::cout<<"hello world"<<std::endl;
    std::cout<<"includes done"<<std::endl;

    initGLFW(3,3);
    
    createWindow(window, "GLMathViz", scr_width, scr_height, framebufferSizeCallback);

    if (!window){
        std::cout<<"could not create window"<< std::endl;
        glfwTerminate();
        return -1;
    }

    // load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<<"can't load GLAD"<<std::endl;
        glfwTerminate();
        return -1;
    }

    //window params
    glfwSwapInterval(1); //v-sync
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //rendering params
    glEnable(GL_DEPTH_TEST);
    glViewport(0,0, scr_width, scr_height);

    //setup programs
    rect.load();

    //timing variables
    double dt = 0.0;
    double lastFrame = 0.0;
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        //update time
        dt = glfwGetTime() - lastFrame;
        lastFrame += dt;
        
        //input
        glfwWaitEventsTimeout(0.001);
        processInput();
        
        //rendering
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        rect.render(dt);
        //move rendered buffer to screen
        glfwSwapBuffers(window);

    }

    //cleanup programs

    rect.cleanup();

    glfwTerminate();

    return 0;
}

void initGLFW(unsigned int versionMajor, unsigned int versionMinor) {
	glfwInit();

	// pass in parameters
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void createWindow(GLFWwindow*& window,
	const char* title, unsigned int width, unsigned int height,
	GLFWframebuffersizefun framebufferSizeCallback) {
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	scr_width = width;
	scr_height = height;
	//updateCameraMatrices();
}

void processInput(){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

