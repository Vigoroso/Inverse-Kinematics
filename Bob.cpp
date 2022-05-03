#include "Bob.h"

Bob::Bob(const std::string& name) : BaseSystem(name)
{
	setVector(Root, 0, -3.0, 4.5);
	ChestXRadius = 1;
	ChestYRadius = 2.5;

	LegOffset = 0.5;
	LegXRadius = 0.2;
	LegYRadius = 1.5;

	FootXRadius = 0.2;
	FootYRadius = 0.2;

	ArmOffsetX = 0.7;
	ArmOffsetY = 2.0;
	ArmXRadius = 2.0;
	ArmYRadius = 0.2;

	HandXRadius = 0.5;
	HandYRadius = 0.3;

	HeadOffSet = 1.2;
	HeadRadius = 1.0;

	NumPointsPerEllipses = 500;

	Theta1 = 0.0 ;
	Theta2 = 0.0 ;
	Theta3 = 0.0 ;
	Theta4 = 0.0;
	Theta5 = 0.0;
	Theta6 = 0.0;
	Theta7 = 0.0;

	RestArmTheta1 = 0.0;
	RestArmTheta2 = 0.0;
	RestArmTheta3 = 0.0;

	TraversingSpline = false;
	TimeStartedTraversing = 0.0;
}

void Bob::getState(double* p)
{
}

void Bob::setState(double* p)
{
}

void Bob::reset(double time)
{
}

void Bob::display(GLenum mode)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glColor3d(0.0, 1.0, 0.0);
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		// go to root (center of chest
		glTranslated(Root[0], Root[1], Root[2]);

		// draw chest
		glPushMatrix();
		{
			drawEllipses(ChestXRadius, ChestYRadius);
		}
		glPopMatrix();

		// draw left Leg

		glPushMatrix();
		{
			// draw upper left leg
			glTranslated(-LegOffset, -ChestYRadius, 0);
			glTranslated(0, -LegYRadius, 0);
			drawEllipses(LegXRadius, LegYRadius);

			// draw lower left leg
			glTranslated(0, - 2.0 * LegYRadius, 0);
			drawEllipses(LegXRadius, LegYRadius);

			// draw left foot
			glTranslated(0, -LegYRadius - FootYRadius, 0);
			drawEllipses(FootXRadius, FootYRadius);
		}
		glPopMatrix();

		// draw Right Leg

		glPushMatrix();
		{
			// draw upper right leg
			glTranslated(LegOffset, -ChestYRadius, 0);
			glTranslated(0, -LegYRadius, 0);
			drawEllipses(LegXRadius, LegYRadius);

			// draw lower right leg
			glTranslated(0, -2.0 * LegYRadius, 0);
			drawEllipses(LegXRadius, LegYRadius);

			// draw right foot
			glTranslated(0, -LegYRadius - FootYRadius, 0);
			drawEllipses(FootXRadius, FootYRadius);
		}
		glPopMatrix();

		// draw Head 

		glPushMatrix();
		{
			// draw head
			glTranslated(0, HeadOffSet + ChestYRadius, 0);
			drawEllipses(HeadRadius, HeadRadius);
		}
		glPopMatrix();

		// draw Left Arm

		glPushMatrix();
		{
			// draw upper left arm
			glTranslated(-ArmOffsetX, ArmOffsetY, 0);
			glRotated(RestArmTheta1, 1, 0, 0); //rotate shoulder
			glRotated(RestArmTheta2, 0, 1, 0); //rotate shoulder
			glRotated(RestArmTheta3, 0, 0, 1); //rotate shoulder
			glTranslated(-ArmXRadius, 0, 0);
			drawEllipses(ArmXRadius, ArmYRadius);

			// draw lower left arm
			glTranslated(- 2.0 * ArmXRadius, 0, 0);
			drawEllipses(ArmXRadius, ArmYRadius);

			// draw left hand
			glTranslated(- ArmXRadius - HandXRadius, 0, 0);
			drawEllipses(HandXRadius, HandYRadius);
		}
		glPopMatrix();

		// draw Right Arm

		glPushMatrix();
		{
			// draw upper Right arm
			glTranslated(ArmOffsetX, ArmOffsetY, 0);
			glRotated(Theta1, 1, 0, 0); //rotate shoulder
			glRotated(Theta2, 0, 1, 0); //rotate shoulder
			glRotated(Theta3, 0, 0, 1); //rotate shoulder
			glTranslated(ArmXRadius, 0, 0);
			drawEllipses(ArmXRadius, ArmYRadius);

			// draw lower Right arm
			glTranslated(ArmXRadius, 0, 0);
			glRotated(Theta4, 1, 0, 0); // rotate elbow
			glRotated(Theta5, 0, 1, 0); // rotate elbow
			glTranslated(ArmXRadius, 0, 0);
			drawEllipses(ArmXRadius, ArmYRadius);

			// draw Right hand
			glTranslated(ArmXRadius, 0, 0);
			glRotated(Theta6, 0, 0, 1); // rotate hand
			glRotated(Theta7, 0, 1, 0); // rotate hand
			glTranslated(HandXRadius, 0, 0);
			drawEllipses(HandXRadius, HandYRadius);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

int Bob::command(int argc, myCONST_SPEC char** argv)
{
	if (argc < 1)
	{
		animTcl::OutputMessage("system %s: wrong number of params.");
		return TCL_ERROR;
	}
	else if (strcmp(argv[0], "position") == 0)
	{
		if (argc != 4)
		{
			animTcl::OutputMessage("system %s: wrong number of params for set.", m_name.c_str());
			return TCL_ERROR;
		}
		else
		{

			setVector(Root, std::stod(argv[1]), std::stod(argv[2]), std::stod(argv[3]));
		}
	}
	return TCL_OK;
}

void Bob::drawEllipses(double xRadius, double yRadius)
{
	glBegin(GL_LINE_STRIP);
	for (float theta = 0.0f; theta <= (2.0f * PI); theta += ((2.0f * PI) / (double)NumPointsPerEllipses))
	{
		double x = cos(theta) * xRadius;
		double y = sin(theta) * yRadius;
		glVertex3f(x, y, 0);
	}
	glEnd();
}
