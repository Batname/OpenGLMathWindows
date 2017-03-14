#pragma once

#include <glm/glm.hpp>

#include "BasePrimitive.h"

class BaseModel : public BasePrimitive
{
public:
	BaseModel(class Shader *shader);
	~BaseModel();

protected:
	glm::mat4 model;

	/* overridible methods */
	virtual void Bind() override;
	virtual void Render() override;
private:
};

