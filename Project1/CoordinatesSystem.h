#pragma once

#include "BasePrimitive.h"

class CoordinatesSystem : public BasePrimitive
{
public:
	CoordinatesSystem(class Shader *shader);
	~CoordinatesSystem();

	virtual void Bind() override;
	virtual void Render() override;

protected:
private:
};