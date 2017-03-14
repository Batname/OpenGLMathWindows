#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

class BasePrimitive
{
public:
	BasePrimitive(class Shader *shader);
	~BasePrimitive();

protected:
	glm::vec3 *Vertices;
	unsigned int NumVertices;
	unsigned int SizeVertices;

	unsigned short *Indices;
	unsigned int NumIndices;
	unsigned int SizeIndices;

	GLuint VBO, VAO, EBO;

	class Shader *myShader;

	/* overridible methods */
	virtual void Bind();
	virtual void Render();
private:
};

