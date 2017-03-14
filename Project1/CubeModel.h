#pragma once

#include "BaseModel.h"

class CubeModel : public BaseModel
{
public:
	CubeModel(class Shader *shader);
	~CubeModel();

	virtual void Bind() override;
	virtual void Render() override;

protected:
private:

};