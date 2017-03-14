#include "VectorScalar.h"

#include "Camera.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern Camera *camera;
using namespace glm;

VectorScalar::VectorScalar(Shader * shader) : BasePrimitive(shader)
{
	// Vectors
	vec3 vertices[8];

	// original vector
	vertices[0] = vec3(-1.0f, 1.0f, 1.0f);
	vertices[1] = vec3(0.0f, 1.0f, 1.0f);

	// origin
	vertices[2] = vec3(0.0f, 0.0f, 0.0f);
	vertices[3] = vec3(0.0f, 1.0f, 1.0f);

	// scalar * 2
	vertices[4] = vertices[0] * 2.0f;
	vertices[5] = vec3(1.0f, 1.0f, 0.0f);

	// origin
	vertices[6] = vec3(0.0f, 0.0f, 0.0f);
	vertices[7] = vec3(1.0f, 1.0f, 1.0f);

	NumVertices = NUM_ARRAY_ELEMENTS(vertices);
	SizeVertices = sizeof(vertices);

	Vertices = new vec3[NumVertices];
	memcpy(Vertices, vertices, SizeVertices);

}

VectorScalar::~VectorScalar()
{
}

void VectorScalar::Bind()
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

void VectorScalar::Render()
{
	BasePrimitive::Render();

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
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	// Transformation
	GLuint projectionLoc = glGetUniformLocation(myShader->Program, "projectionMatrix");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLuint viewLoc = glGetUniformLocation(myShader->Program, "viewMatrix");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLuint modelLoc = glGetUniformLocation(myShader->Program, "modelMatrix");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_LINES, 0, 4);
	glBindVertexArray(0);
}
