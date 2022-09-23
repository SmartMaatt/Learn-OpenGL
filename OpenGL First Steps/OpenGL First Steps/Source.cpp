#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Function headers
bool checkShaderCompileErrors(unsigned int shader);
bool checkLinkingErrors(unsigned int shaderProgram);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Parameters
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

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



	// Build and compile vertex shader.
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check for shader compile errors.
	if (!checkShaderCompileErrors(vertexShader)) { return -1; }

	// Build and compile fragment shader.
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check for shader compile errors.
	if (!checkShaderCompileErrors(fragmentShader)) { return -1; }

	// Creating shader program.
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors.
	if (!checkLinkingErrors(shaderProgram)) { return -1; }
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// VBO buffer initialization.
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);



	// Program Loop.
	while (!glfwWindowShouldClose(window))
	{
		// User input.
		processInput(window);

		// Rendering commands here.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Check and call events and swap the buffers.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Program shutdown.
	glfwTerminate();
	return 0;
}


/// <summary>
/// Checks the status of linking the shader buffers to the program.
/// </summary>
/// <param name="shaderProgram">Shader buffer.</param>
/// <returns>True if linking was correct, False otherwise.</returns>
bool checkLinkingErrors(unsigned int shaderProgram)
{
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

/// <summary>
/// Checks the status of compiling of shader buffer.
/// </summary>
/// <param name="shader">Shader buffer</param>
/// <returns>True if compiling was correct, False otherwise.</returns>
bool checkShaderCompileErrors(unsigned int shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
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