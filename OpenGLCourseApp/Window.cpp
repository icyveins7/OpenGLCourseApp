#include "Window.h"

Window::Window() {
	width = 800;
	height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight) {
	width = windowWidth;
	height = windowHeight;
}

int Window::initialise() {
	// Initialise GLFW
	if (!glfwInit()) {
		printf("GLFW Init failed.\n");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Test window", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW window creation failed.\n");
		glfwTerminate();
		return 2;
	}

	// Get Buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("glew Init failed.\n");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 3;
	}

	glEnable(GL_DEPTH_TEST); // for depth-testing

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
}

Window::~Window() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}