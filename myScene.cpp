////////////////////////////////////////////////////
// // Template code for  CS 174C
////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <shared/defs.h>

#include "shared/opengl.h"

#include <string.h>
#include <util/util.h>
#include <GLModel/GLModel.h>
#include "anim.h"
#include "animTcl.h"
#include "myScene.h"
#include "SampleParticle.h"
#include "SampleGravitySimulator.h"
#include "HermiteSpline.h"
#include "TankPath.h"
#include "Tank.h"
#include "Missile.h"
#include "MissilePathSimulator.h"
#include "ParticleSystem.h"
#include "ParticlePhysicsSimulator.h"
#include "Hermite.h"
#include "Classroom.h"
#include "IKSim.h"
#include "Bob.h"

//#include <util/jama/tnt_stopwatch.h>
//#include <util/jama/jama_lu.h>

// register a sample variable with the shell.
// Available types are:
// - TCL_LINK_INT 
// - TCL_LINK_FLOAT

int g_testVariable = 10;

SETVAR myScriptVariables[] = {
	"testVariable", TCL_LINK_INT, (char *) &g_testVariable,
	"",0,(char *) NULL
};


//---------------------------------------------------------------------------------
//			Hooks that are called at appropriate places within anim.cpp
//---------------------------------------------------------------------------------

// start or end interaction
void myMouse(int button, int state, int x, int y)
{

	// let the global resource manager know about the new state of the mouse 
	// button
	GlobalResourceManager::use()->setMouseButtonInfo( button, state );

	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		animTcl::OutputMessage(
			"My mouse received a mouse button press event\n");

	}
	if( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
	{
		animTcl::OutputMessage(
			"My mouse received a mouse button release event\n") ;
	}
}	// myMouse

// interaction (mouse motion)
void myMotion(int x, int y)
{

	GLMouseButtonInfo updatedMouseButtonInfo = 
		GlobalResourceManager::use()->getMouseButtonInfo();

	if( updatedMouseButtonInfo.button == GLUT_LEFT_BUTTON )
	{
		animTcl::OutputMessage(
			"My mouse motion callback received a mousemotion event\n") ;
	}

}	// myMotion

static int  Part1SetUp(ClientData clientData, Tcl_Interp* interp, int argc, myCONST_SPEC char** argv)
{
	bool success;

	//Clear system
	GlobalResourceManager::use()->clearAll();

	// register a system
	HermiteSpline* hermite = new HermiteSpline("hermite", false);
	success = GlobalResourceManager::use()->addSystem(hermite, true);

	isPart2 = false;
	// make sure it was registered successfully
	assert(success);
	return TCL_OK;
}

static int  Part2SetUp(ClientData clientData, Tcl_Interp* interp, int argc, myCONST_SPEC char** argv)
{
	bool success;

	//Clear system
	GlobalResourceManager::use()->clearAll();

	Tank* tank = new Tank("tankpath");
	success = GlobalResourceManager::use()->addSystem(tank, true);

	// make sure it was registered successfully
	assert(success);

	// register a system
	TankPath* tankpath = new TankPath("tanksimulator", tank);
	success = GlobalResourceManager::use()->addSimulator(tankpath, true);

	assert(success);

	Missile* missle = new Missile("missile");
	success = GlobalResourceManager::use()->addSystem(missle, true);

	// make sure it was registered successfully
	assert(success);

	// register a system
	MissilePathSimulator* missilePath = new MissilePathSimulator("missilePath", missle, tank);
	success = GlobalResourceManager::use()->addSimulator(missilePath, true);

	// make sure it was registered successfully
	assert(success);
	return TCL_OK;
}

void ParticleSpringMassSystem()
{
	bool success;
	//Clear system
	GlobalResourceManager::use()->clearAll();

	// register a system
	ParticleSystem* particleSys = new ParticleSystem("partSys");
	success = GlobalResourceManager::use()->addSystem(particleSys, true);

	// register a system
	ParticlePhysicsSimulator* particlePhys = new ParticlePhysicsSimulator("partSim");
	success = GlobalResourceManager::use()->addSimulator(particlePhys, true);
}
void MakeScene(void)
{
	bool success;
	Classroom* classroom = new Classroom("classroom");
	success = GlobalResourceManager::use()->addSystem(classroom, true);
	Bob* bob = new Bob("bob");
	success = GlobalResourceManager::use()->addSystem(bob, true);
	IKSim* ikSim = new IKSim("iksim", bob);;
	success = GlobalResourceManager::use()->addSimulator(ikSim, true);
}	// MakeScene

// OpenGL initialization
void myOpenGLInit(void)
{
	animTcl::OutputMessage("Initialization routine was called.");

}	// myOpenGLInit

void myIdleCB(void)
{
	
	return;

}	// myIdleCB

void myKey(unsigned char key, int x, int y)
{
	 animTcl::OutputMessage("My key callback received a key press event\n");
	return;

}	// myKey

static int testGlobalCommand(ClientData clientData, Tcl_Interp *interp, int argc, myCONST_SPEC char **argv)
{
	 animTcl::OutputMessage("This is a test command!");
    animTcl::OutputResult("100") ;
	return TCL_OK;

}	// testGlobalCommand

void mySetScriptCommands(Tcl_Interp *interp)
{

	// here you can register additional generic (they do not belong to any object) 
	// commands with the shell

	Tcl_CreateCommand(interp, "test", testGlobalCommand, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);

	Tcl_CreateCommand(interp, "part1", Part1SetUp, (ClientData)NULL,
		(Tcl_CmdDeleteProc*)NULL);

	Tcl_CreateCommand(interp, "part2", Part2SetUp, (ClientData)NULL,
		(Tcl_CmdDeleteProc*)NULL);

}	// mySetScriptCommands
