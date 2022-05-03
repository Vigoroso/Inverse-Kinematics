#pragma once
#include "BaseSimulator.h"
#include <GLModel/GLModel.h>
#include <shared/defs.h>
#include <util/util.h>
#include "animTcl.h"
#include "BaseSimulator.h"
#include "BaseSystem.h"
#include "ParticleSystem.h"
#include "Spring.h"
#include "GlobalResourceManager.h"
#include "Hermite.h"
#include "Bob.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#ifdef Success
#undef Success
#endif
#include "Eigen/Dense"
#include <Eigen/Core>

#include <string>

// a sample simulator

class IKSim : public BaseSimulator
{
public:

	IKSim(const std::string& name, Bob* bob);

	int step(double time);
	int init(double time)
	{
		return 0;
	};

	int command(int argc, myCONST_SPEC char** argv);

	void computeThetas(double* thetas, double time, double* deltaX);

	Hermite* Curve;
	Bob* B0B;

	glm::mat4 XDeriv(double theta);
	glm::mat4 YDeriv(double theta);
	glm::mat4 ZDeriv(double theta);
};

