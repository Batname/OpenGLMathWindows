#pragma once

#include "BaseModel.h"

class VectorsCubeModel : public BaseModel
{
public:
	VectorsCubeModel(class Shader *shader);
	~VectorsCubeModel();

	virtual void Bind() override;
	virtual void Render() override;

protected:
private:

};

