#pragma once

#include "Camera.h"

extern Camera *camera;

extern GLfloat deltaTime;
extern GLfloat lastFrame;

bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

// Moves/alters the camera positions based on user input
void Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera->ProcessKeyboard(Camera::FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera->ProcessKeyboard(Camera::BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera->ProcessKeyboard(Camera::LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera->ProcessKeyboard(Camera::RIGHT, deltaTime);
	if (keys[GLFW_KEY_R])
		camera->ProcessKeyboard(Camera::UPWARD, deltaTime);
	if (keys[GLFW_KEY_F])
		camera->ProcessKeyboard(Camera::DOWN, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}