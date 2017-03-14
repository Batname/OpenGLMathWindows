#include "BasePrimitive.h"

#include "Shader.h"

BasePrimitive::BasePrimitive(Shader *shader) : myShader(shader)
{
}

BasePrimitive::~BasePrimitive()
{
	if (Vertices !=nullptr) delete Vertices;
	if (Indices != nullptr) delete Indices;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void BasePrimitive::Bind()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

}

void BasePrimitive::Render()
{
	myShader->Use();
	glBindVertexArray(VAO);
}
