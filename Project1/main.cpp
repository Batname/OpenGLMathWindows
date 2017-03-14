// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include "Shader.h"
#include "callbacks.h"
#include "Camera.h"

// graphics
#include "CoordinatesSystem.h"
#include "CubeModel.h"
#include "VectorsCubeModel.h"

// examples
#include "VectorScalar.h"

// Window dimensions
GLuint WIDTH = 1200, HEIGHT = 800;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLFWwindow* window;
Camera *camera;


// The MAIN function, from here we start the application and run the game loop
int main()
{

	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RELEASE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);


	// Set the camera
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	// Build and compile our shader program
	Shader ourShader("./assets/shaders/vertex.glsl", "./assets/shaders/fragment.glsl");

	CoordinatesSystem coordinatesSystem(&ourShader);
	coordinatesSystem.Bind();

	CubeModel cubeModel(&ourShader);
	cubeModel.Bind();

	Shader vectorShader("./assets/shaders/vectors.glsl", "./assets/shaders/fragment.glsl");
	VectorsCubeModel vectorsCubeModel(&vectorShader);
	vectorsCubeModel.Bind();

	// examples
	VectorScalar vectorScalarExmple(&vectorShader);
	vectorScalarExmple.Bind();

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		Do_Movement();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		coordinatesSystem.Render();
		cubeModel.Render();
		vectorsCubeModel.Render();

		// examples
		vectorScalarExmple.Render();

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	delete camera;
	return 0;
}
