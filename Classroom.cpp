#include "Classroom.h"

Classroom::Classroom(const std::string& name) : BaseSystem(name)
{
}

void Classroom::getState(double* p)
{
}

void Classroom::setState(double* p)
{
}

void Classroom::reset(double time)
{
}

void Classroom::display(GLenum mode)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// Draw Wall
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-10.0, -12.0, -0.05);
	glVertex3f(-10.0, 7.5, -0.05);
	glVertex3f(10.0, 7.5, -0.05);
	glVertex3f(10.0, -12.0, -0.05);
	glEnd();

	// Draw Floor
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-10.0, -12.0, -0.05);
	glVertex3f(-10.0, -12.0, 10.0);
	glVertex3f(10.0, -12.0, 10.0);
	glVertex3f(10.0, -12.0, -0.05);
	glEnd();

	// Draw Blackboard
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-7.5, -5.0, 0.0);
	glVertex3f(-7.5, 5.0, 0.0);
	glVertex3f(7.5, 5.0, 0.0);
	glVertex3f(7.5, -5.0, 0.0);
	glEnd();

	//glRectd(-5.0, -5.0, 0.0, 0.0);
	glPopMatrix();
	glPopAttrib();
}

int Classroom::command(int argc, myCONST_SPEC char** argv)
{
	return 0;
}
