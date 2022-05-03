#pragma once
#include "BaseSystem.h"
#include "HermiteSpline.h"
class Classroom : public BaseSystem
{
public:
	Classroom(const std::string& name);
	virtual void getState(double* p);
	virtual void setState(double* p);
	void reset(double time);

	void display(GLenum mode = GL_RENDER);

	void readModel(char* fname) { m_model.ReadOBJ(fname); }
	int command(int argc, myCONST_SPEC char** argv);

protected:
	GLMmodel m_model;
};
