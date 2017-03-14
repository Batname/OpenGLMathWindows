#pragma once

#include <GLFW/glfw3.h>

// GL Includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:

	// Default camera values
	constexpr static GLfloat YAW = -90.0f;
	constexpr static GLfloat PITCH = 0.0f;
	constexpr static GLfloat SPEED = 3.0f;
	constexpr static GLfloat SENSITIVTY = 0.25f;
	constexpr static GLfloat ZOOM = 45.0f;

public:
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UPWARD,
		DOWN
	};

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);
	~Camera();

	glm::mat4 GetViewMatrix() const;

	void ProcessMouseScroll(GLfloat yoffset);
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

	// getters
	inline GLfloat GetZoom() const { return Zoom; }
	glm::mat4 GetProjection() const;

protected:
private:
	void updateCameraVectors();

	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;
};