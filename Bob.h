#pragma once
#include "BaseSystem.h"
#include "Bob.h"
class Bob : public BaseSystem
{
public:
	Bob(const std::string& name);
	virtual void getState(double* p);
	virtual void setState(double* p);
	void reset(double time);

	void display(GLenum mode = GL_RENDER);

	int command(int argc, myCONST_SPEC char** argv);

	bool TraversingSpline;
	double TimeStartedTraversing;

	Vector Root;
	double ChestXRadius;
	double ChestYRadius;

	double LegOffset;

	double LegXRadius;
	double LegYRadius;

	double FootXRadius;
	double FootYRadius;

	double ArmOffsetX;
	double ArmOffsetY;
	double ArmXRadius;
	double ArmYRadius;

	double HandXRadius;
	double HandYRadius;

	double HeadOffSet;
	double HeadRadius;

	double NumPointsPerEllipses;

	double Theta1;
	double Theta2;
	double Theta3;
	double Theta4;
	double Theta5;
	double Theta6;
	double Theta7;

	double CurrTheta1;
	double CurrTheta2;
	double CurrTheta3;
	double CurrTheta4;
	double CurrTheta5;
	double CurrTheta6;
	double CurrTheta7;

	double RestArmTheta1;
	double RestArmTheta2;
	double RestArmTheta3;

protected:
	void drawEllipses(double xRadius, double yRadius);
};