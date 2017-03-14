#pragma once

#include "BasePrimitive.h"

class VectorScalar : BasePrimitive
{
public:
	VectorScalar(class Shader *shader);
	~VectorScalar();

	virtual void Bind() override;
	virtual void Render() override;
protected:
private:

};

