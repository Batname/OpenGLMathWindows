#include "CoordinatesSystem.h"

#include "Camera.h"
#include "Shader.h"

#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern Camera *camera;

using namespace glm;

CoordinatesSystem::CoordinatesSystem(Shader *shader) : BasePrimitive(shader)
{
	// Set up vertex data (and buffer(s)) and attribute pointers
	vec3 vertices[] = {
		// Positions         // Colors
		vec3(0.5f,  0.0f,  0.0f),   vec3(1.0f, 1.0f, 1.0f),  // X main
		vec3(-0.5f,  0.0f,  0.0f),   vec3(1.0f, 1.0f, 1.0f),  // X main
		vec3(0.5f,  0.0f,  0.25f),   vec3(1.0f, 0.0f, 0.0f), // X 1l
		vec3(-0.5f,  0.0f,  0.25f),   vec3(1.0f, 0.0f, 0.0f), // X 1l
		vec3(0.5f,  0.0f, -0.25f),   vec3(1.0f, 0.0f, 0.0f), // X 1r
		vec3(-0.5f,  0.0f, -0.25f),   vec3(1.0f, 0.0f, 0.0f), // X 1r

		vec3(0.5f,  0.0f,  0.5f),   vec3(1.0f, 0.0f, 0.0f),  // X 2l
		vec3(-0.5f,  0.0f,  0.5f),   vec3(1.0f, 0.0f, 0.0f),  // X 2l
		vec3(0.5f,  0.0f, -0.5f),   vec3(1.0f, 0.0f, 0.0f),  // X 2r
		vec3(-0.5f,  0.0f, -0.5f),   vec3(1.0f, 0.0f, 0.0f),  // X 2r

		vec3(0.0f,  0.5f,  0.0f),   vec3(1.0f, 1.0f, 1.0f),  // Y main
		vec3(0.0f, -0.5f,  0.0f),   vec3(1.0f, 1.0f, 1.0f),  // Y main

		vec3(0.0f,  0.0f, -0.5f),   vec3(1.0f, 1.0f, 1.0f),  // Z main
		vec3(0.0f,  0.0f,  0.5f),   vec3(1.0f, 1.0f, 1.0f),  // Z main
		vec3(0.25f,  0.0f, -0.5f),   vec3(1.0f, 0.0f, 0.0f), // Z 1l
		vec3(0.25f,  0.0f,  0.5f),   vec3(1.0f, 0.0f, 0.0f), // Z 1l
		vec3(-0.25f,  0.0f, -0.5f),   vec3(1.0f, 0.0f, 0.0f), // Z 1r
		vec3(-0.25f,  0.0f,  0.5f),   vec3(1.0f, 0.0f, 0.0f), // Z 1r

		vec3(0.5f,  0.0f, -0.5f),   vec3(1.0f, 0.0f, 0.0f),  // Z 2l
		vec3(0.5f,  0.0f,  0.5f),   vec3(1.0f, 0.0f, 0.0f),  // Z 2l
		vec3(-0.5f,  0.0f, -0.5f),   vec3(1.0f, 0.0f, 0.0f),  // Z 2r
		vec3(-0.5f,  0.0f,  0.5f),   vec3(1.0f, 0.0f, 0.0f)   // Z 2r
	};

	NumVertices = NUM_ARRAY_ELEMENTS(vertices);
	SizeVertices = sizeof(vertices);

	Vertices = new vec3[NumVertices];
	memcpy(Vertices, vertices, SizeVertices);
}

CoordinatesSystem::~CoordinatesSystem()
{
}

void CoordinatesSystem::Bind()
{
	BasePrimitive::Bind();

	glBufferData(GL_ARRAY_BUFFER, SizeVertices, Vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// clear
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CoordinatesSystem::Render()
{
	BasePrimitive::Render();

	// Transformation matrix
	glm::mat4 transformMatrix;

	// View camera matrix
	glm::mat4 view;
	view = camera->GetViewMatrix();

	// Projection matrix
	glm::mat4 projection;
	projection = camera->GetProjection();

	// Model matrix
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(7.0f, 2.0f, 7.0f));

	// All matrix together
	transformMatrix = projection * view * model;

	// Transformation
	GLuint transformLoc = glGetUniformLocation(myShader->Program, "transformMatrix");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMatrix));

	glDrawArrays(GL_LINES, 0, 22);
	glBindVertexArray(0);
}
