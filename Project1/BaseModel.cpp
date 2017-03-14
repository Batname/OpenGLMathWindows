#include "BaseModel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

BaseModel::BaseModel(Shader *shader) : BasePrimitive(shader)
{
	model = glm::translate(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
}

BaseModel::~BaseModel()
{

}

void BaseModel::Bind()
{
	BasePrimitive::Bind();
}

void BaseModel::Render()
{
	BasePrimitive::Render();
}
