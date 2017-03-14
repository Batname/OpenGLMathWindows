#include "VectorsCubeModel.h"

#include "Camera.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern Camera *camera;
using namespace glm;

VectorsCubeModel::VectorsCubeModel(Shader *shader) : BaseModel(shader)
{
	// Vectors
	vec3 vectorVertices[] =
	{
		vec3(-1.0f,  1.0f,  1.0f),   vec3(0.0f, 0.0f, 1.0f),  // 1
		vec3(0.0f,  0.0f,  0.0f),   vec3(0.0f, 0.0f, 1.0f),  // origin
		vec3(1.0f,  1.0f,  1.0f),   vec3(0.0f, 0.0f, 1.0f),  // 2
		vec3(0.0f,  0.0f,  0.0f),   vec3(0.0f, 0.0f, 1.0f),  // origin
		vec3(1.0f,  1.0f, -1.0f),   vec3(0.0f, 0.0f, 1.0f),  // 3
		vec3(0.0f,  0.0f,  0.0f),   vec3(0.0f, 0.0f, 1.0f),  // origin
		vec3(-1.0f,  1.0f, -1.0f),   vec3(0.0f, 0.0f, 1.0f),  // 4
		vec3(0.0f,  0.0f,  0.0f),   vec3(0.0f, 0.0f, 1.0f),  // origin
		vec3(1.0f, -1.0f, -1.0f),   vec3(0.0f, 0.0f, 1.0f),  // 5
		vec3(0.0f,  0.0f,  0.0f),   vec3(0.0f, 0.0f, 1.0f),  // origin
		vec3(-1.0f, -1.0f, -1.0f),   vec3(0.0f, 0.0f, 1.0f),  // 6
		vec3(0.0f,  0.0f,  0.0f),   vec3(0.0f, 0.0f, 1.0f),  // origin
		vec3(1.0f, -1.0f,  1.0f),   vec3(0.0f, 0.0f, 1.0f),  // 7
		vec3(0.0f,  0.0f,  0.0f),   vec3(0.0f, 0.0f, 1.0f),  // origin
		vec3(-1.0f, -1.0f,  1.0f),   vec3(0.0f, 0.0f, 1.0f),  // 8
		vec3(0.0f,  0.0f,  0.0f),   vec3(0.0f, 0.0f, 1.0f),  // origin
	};

	NumVertices = NUM_ARRAY_ELEMENTS(vectorVertices);
	SizeVertices = sizeof(vectorVertices);

	Vertices = new vec3[NumVertices];
	memcpy(Vertices, vectorVertices, SizeVertices);
}


VectorsCubeModel::~VectorsCubeModel()
{
}

void VectorsCubeModel::Bind()
{
	BaseModel::Bind();

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

void VectorsCubeModel::Render()
{
	BaseModel::Render();

	// View camera matrix
	glm::mat4 view;
	view = camera->GetViewMatrix();

	// Projection matrix
	glm::mat4 projection;
	projection = camera->GetProjection();

	// Transformation
	GLuint projectionLoc = glGetUniformLocation(myShader->Program, "projectionMatrix");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLuint viewLoc = glGetUniformLocation(myShader->Program, "viewMatrix");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLuint modelLoc = glGetUniformLocation(myShader->Program, "modelMatrix");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_LINES, 0, 16);
	glBindVertexArray(0);
}