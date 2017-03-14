#include "CubeModel.h"

#include "Camera.h"
#include "Shader.h"

#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern Camera *camera;
using namespace glm;

CubeModel::CubeModel(Shader *shader) :  BaseModel(shader)
{
	vec3 cubeVertices[] =
	{
		vec3(-1.0f, +1.0f, +1.0f),  // 0
		vec3(+0.0f, +1.0f, +0.0f),	// Color
		vec3(+1.0f, +1.0f, +1.0f),  // 1
		vec3(+0.0f, +1.0f, +0.0f),	// Color
		vec3(+1.0f, +1.0f, -1.0f),  // 2
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(-1.0f, +1.0f, -1.0f),  // 3
		vec3(+0.0f, +1.0f, +0.0f),  // Color

		vec3(-1.0f, +1.0f, -1.0f),  // 4
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(+1.0f, +1.0f, -1.0f),  // 5
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(+1.0f, -1.0f, -1.0f),  // 6
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(-1.0f, -1.0f, -1.0f),  // 7
		vec3(+0.0f, +1.0f, +0.0f),  // Color

		vec3(+1.0f, +1.0f, -1.0f),  // 8
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(+1.0f, +1.0f, +1.0f),  // 9
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(+1.0f, -1.0f, +1.0f),  // 10
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(+1.0f, -1.0f, -1.0f),  // 11
		vec3(+0.0f, +1.0f, +0.0f),  // Color

		vec3(-1.0f, +1.0f, +1.0f),  // 12
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(-1.0f, +1.0f, -1.0f),  // 13
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(-1.0f, -1.0f, -1.0f),  // 14
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(-1.0f, -1.0f, +1.0f),  // 15
		vec3(+0.0f, +1.0f, +0.0f),  // Color

		vec3(+1.0f, +1.0f, +1.0f),  // 16
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(-1.0f, +1.0f, +1.0f),  // 17
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(-1.0f, -1.0f, +1.0f),  // 18
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(+1.0f, -1.0f, +1.0f),  // 19
		vec3(+0.0f, +1.0f, +0.0f),  // Color

		vec3(+1.0f, -1.0f, -1.0f),  // 20
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(-1.0f, -1.0f, -1.0f),  // 21
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(-1.0f, -1.0f, +1.0f),  // 22
		vec3(+0.0f, +1.0f, +0.0f),  // Color
		vec3(+1.0f, -1.0f, +1.0f),  // 23
		vec3(+0.0f, +1.0f, +0.0f),  // Color
	};

	NumVertices = NUM_ARRAY_ELEMENTS(cubeVertices);
	SizeVertices = sizeof(cubeVertices);

	Vertices = new vec3[NumVertices];
	memcpy(Vertices, cubeVertices, SizeVertices);

	unsigned short cubeIndices[] = {
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};

	NumIndices = NUM_ARRAY_ELEMENTS(cubeIndices);
	SizeIndices = sizeof(cubeIndices);
	Indices = new GLushort[NumIndices];
	memcpy(Indices, cubeIndices, SizeIndices);
}

CubeModel::~CubeModel()
{

}

void CubeModel::Bind()
{
	BaseModel::Bind();

	// Bind vectors data
	glBufferData(GL_ARRAY_BUFFER, SizeVertices, Vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeIndices, Indices, GL_STATIC_DRAW);	

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

void CubeModel::Render()
{
	BaseModel::Render();

	// Transformation matrix
	glm::mat4 transformMatrix;

	// View camera matrix
	glm::mat4 view;
	view = camera->GetViewMatrix();

	// Projection matrix
	glm::mat4 projection;
	projection = camera->GetProjection();

	// All matrix together
	transformMatrix = projection * view * model;

	// Transformation
	GLuint transformLoc = glGetUniformLocation(myShader->Program, "transformMatrix");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMatrix));

	glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}
