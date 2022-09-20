#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// Initialize GLFW and define OpenGL version.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac OS X
#endif

	// Create window object.
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Setting OpenGL viewport.
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	
	// Glad initialization.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))	// Address of the OpenGL function pointers which is OS - specific.
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Program Loop.
	while (!glfwWindowShouldClose(window))
	{
		// User input.
		processInput(window);

		// Rendering commands here.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Check and call events and swap the buffers.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Program shutdown.
	glfwTerminate();
	return 0;
}

/// <summary>
/// Resizes glViewport to current window size.
/// </summary>
/// <param name="window">Pointer to window object.</param>
/// <param name="width">New preferred width.</param>
/// <param name="height">New preferred height.</param>
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/// <summary>
/// Determines which of the selected keyboard keys is currently pressed.
/// </summary>
/// <param name="window">Pointer to window object.</param>
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}