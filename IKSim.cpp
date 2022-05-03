#include "IKSim.h"

using namespace glm;

IKSim::IKSim(const std::string& name, Bob* bob) :
	BaseSimulator(name)
{
	B0B = bob;
}	// IKSim

int IKSim::step(double time)
{
	double thetas[7] = { 0 };
	Vector deltaX;

	double speed = 1.0;


	deltaX[0] = 0.0;
	deltaX[1] = 0.0;
	deltaX[2] = -1.0;

	VecScale(deltaX, speed);
	

	computeThetas(thetas, time, deltaX);

	B0B->Theta1 += thetas[0];
	B0B->Theta2 += thetas[1];
	B0B->Theta3 += thetas[2];
	B0B->Theta4 += thetas[3];
	B0B->Theta5 += thetas[4];
	B0B->Theta6 += thetas[5];
	B0B->Theta7 += thetas[6];

	return 0;
}

int IKSim::command(int argc, myCONST_SPEC char** argv)
{
	if (argc < 1)
	{
		animTcl::OutputMessage("system %s: wrong number of params.");
		return TCL_ERROR;
	}
	else if (strcmp(argv[0], "read") == 0)
	{
		if (argc != 2)
		{
			animTcl::OutputMessage("system %s: wrong number of params for set.", m_name.c_str());
			return TCL_ERROR;
		}
		else
		{
			bool success;
			Curve = new Hermite("hermite");
			success = GlobalResourceManager::use()->addSystem(Curve, true);
			Curve->loadFromFile2D(argv[1]);
			B0B->Theta1 = 90.0;
			B0B->Theta2 = -70.0;
			B0B->Theta3 = -10.0;
			B0B->RestArmTheta1 = -90.0;
			B0B->RestArmTheta2 = -70.0;
			B0B->RestArmTheta3 = -10.0;
		}
	}
	return TCL_OK;
}

void IKSim::computeThetas(double* thetas, double time, double* deltaX)
{
	mat4 tRoot = glm::translate(glm::mat4(1.0), glm::vec3(B0B->Root[0], B0B->Root[1], B0B->Root[2]));

	mat4 tSh = glm::translate(glm::mat4(1.0), glm::vec3(B0B->ArmOffsetX, B0B->ArmOffsetY, 0.0));

	mat4 RzTheta3 = glm::rotate(glm::mat4(1.0), glm::radians((float)B0B->Theta3), glm::vec3(0.0, 0.0, 1.0));

	mat4 RyTheta2 = glm::rotate(glm::mat4(1.0), glm::radians((float)B0B->Theta2), glm::vec3(0.0, 1.0, 0.0));

	mat4 RxTheta1 = glm::rotate(glm::mat4(1.0), glm::radians((float)B0B->Theta1), glm::vec3(1.0, 0.0, 0.0));

	mat4 tEl = glm::translate(glm::mat4(1.0), glm::vec3(2.0 * B0B->ArmXRadius, 0.0, 0.0));

	mat4 RyTheta5 = glm::rotate(glm::mat4(1.0), glm::radians((float)B0B->Theta5), glm::vec3(0.0, 1.0, 0.0));

	mat4 RxTheta4 = glm::rotate(glm::mat4(1.0), glm::radians((float)B0B->Theta4), glm::vec3(1.0, 0.0, 0.0));

	mat4 tWr = glm::translate(glm::mat4(1.0), glm::vec3(2.0 * B0B->ArmXRadius, 0.0, 0.0));

	mat4 RyTheta7 = glm::rotate(glm::mat4(1.0), glm::radians((float)B0B->Theta7), glm::vec3(0.0, 1.0, 0.0));

	mat4 RzTheta6 = glm::rotate(glm::mat4(1.0), glm::radians((float)B0B->Theta6), glm::vec3(0.0, 0.0, 1.0));

	vec4 tHand = vec4(1.0);
	tHand[0] = 2 * B0B->HandXRadius;
	tHand[1] = 0.0;
	tHand[2] = 0.0;

	mat4 RzTheta3Deriv = ZDeriv(B0B->Theta3);

	mat4 RyTheta2Deriv = YDeriv(B0B->Theta2);

	mat4 RxTheta1Deriv = XDeriv(B0B->Theta1);

	mat4 RyTheta5Deriv = YDeriv(B0B->Theta5);

	mat4 RxTheta4Deriv = XDeriv(B0B->Theta4);

	mat4 RyTheta7Deriv = YDeriv(B0B->Theta7);

	mat4 RzTheta6Deriv = ZDeriv(B0B->Theta6);

	//double Jacobian[4][7];

	mat4 temp = tRoot * tSh;
	temp = tRoot * tSh;
	temp = temp * RxTheta1Deriv;
	temp = temp * RyTheta2;
	temp = temp * RzTheta3;
	temp = temp * tEl;
	temp = temp * RxTheta4;
	temp = temp * RyTheta5;
	temp = temp * tWr;
	temp = temp * RzTheta6;
	temp = temp * RyTheta7;
	vec4 col1 = temp * tHand;

	temp = mat4(0.0);
	temp = tRoot * tSh;
	temp = temp * RxTheta1;
	temp = temp * RyTheta2Deriv;
	temp = temp * RzTheta3;
	temp = temp * tEl;
	temp = temp * RxTheta4;
	temp = temp * RyTheta5;
	temp = temp * tWr;
	temp = temp * RzTheta6;
	temp = temp * RyTheta7;
	vec4 col2 = temp * tHand;

	temp = mat4(0.0);
	temp = tRoot * tSh;
	temp = temp * RxTheta1;
	temp = temp * RyTheta2;
	temp = temp * RzTheta3Deriv;
	temp = temp * tEl;
	temp = temp * RxTheta4;
	temp = temp * RyTheta5;
	temp = temp * tWr;
	temp = temp * RzTheta6;
	temp = temp * RyTheta7;
	vec4 col3 = temp * tHand;

	temp = mat4(0.0);
	temp = tRoot * tSh;
	temp = temp * RxTheta1;
	temp = temp * RyTheta2;
	temp = temp * RzTheta3;
	temp = temp * tEl;
	temp = temp * RxTheta4Deriv;
	temp = temp * RyTheta5;
	temp = temp * tWr;
	temp = temp * RzTheta6;
	temp = temp * RyTheta7;
	vec4 col4 = temp * tHand;

	temp = mat4(0.0);
	temp = tRoot * tSh;
	temp = temp * RxTheta1;
	temp = temp * RyTheta2;
	temp = temp * RzTheta3;
	temp = temp * tEl;
	temp = temp * RxTheta4;
	temp = temp * RyTheta5Deriv;
	temp = temp * tWr;
	temp = temp * RzTheta6;
	temp = temp * RyTheta7;
	vec4 col5 = temp * tHand;

	temp = mat4(0.0);
	temp = tRoot * tSh;
	temp = temp * RxTheta1;
	temp = temp * RyTheta2;
	temp = temp * RzTheta3;
	temp = temp * tEl;
	temp = temp * RyTheta5;
	temp = temp * RyTheta5;
	temp = temp * tWr;
	temp = temp * RzTheta6Deriv;
	temp = temp * RyTheta7;
	vec4 col6 = temp * tHand;

	temp = mat4(0.0);
	temp = tRoot * tSh;
	temp = temp * RxTheta1;
	temp = temp * RyTheta2;
	temp = temp * RzTheta3;
	temp = temp * tEl;
	temp = temp * RxTheta4;
	temp = temp * RyTheta5;
	temp = temp * tWr;
	temp = temp * RzTheta6;
	temp = temp * RyTheta7Deriv;
	vec4 col7 = temp * tHand;

	
	temp = mat4(0.0);
	temp = tRoot * tSh;
	temp = temp * RxTheta1;
	temp = temp * RyTheta2;
	temp = temp * RzTheta3;
	temp = temp * tEl;
	temp = temp * RxTheta4;
	temp = temp * RyTheta5;
	temp = temp * tWr;
	temp = temp * RzTheta6;
	temp = temp * RyTheta7;

	vec4 HandPos = temp * tHand;

	VectorObj s;
	Vector DistToPoint;
	if (B0B->TraversingSpline)
	{
		if (((time - B0B->TimeStartedTraversing) / 10.0) > 1)
		{
			B0B->TraversingSpline = false;
			return;
		}

		s = Curve->getIntermediatePoint((time - B0B->TimeStartedTraversing) / 10.0);
		DistToPoint[0] = s[0] - HandPos[0];
		DistToPoint[1] = s[1] - HandPos[1];
		DistToPoint[2] = s[2] - HandPos[2];
	}
	else
	{
		s = Curve->getIntermediatePoint(0);
		DistToPoint[0] = s[0] - HandPos[0];
		DistToPoint[1] = s[1] - HandPos[1];
		DistToPoint[2] = s[2] - HandPos[2];

		double length = Norm(DistToPoint, 3);

		if (length < 0.1)
		{
			B0B->TimeStartedTraversing = time;
			B0B->TraversingSpline = true;
			return;
		}

		VecScale(DistToPoint, 1.0 / length);
		double speed = 1.0;

		VecScale(DistToPoint, speed * 0.1);
	}

	Eigen::MatrixXf jacobian(3, 7);
	Eigen::MatrixXf jacobianTranspose(7, 3); 

	for (int i = 0; i < 3; i++)
	{
		jacobian(i, 0) = col1[i];
		jacobian(i, 1) = col2[i];
		jacobian(i, 2) = col3[i];
		jacobian(i, 3) = col4[i];
		jacobian(i, 4) = col5[i];
		jacobian(i, 5) = col6[i];
		jacobian(i, 6) = col7[i];
	}
	jacobianTranspose = jacobian.transpose();

	Eigen::Matrix3f a = jacobian * jacobianTranspose;
	Eigen::Vector3f b;
	for (int i = 0; i < 3; i++)
	{
		b(i) = DistToPoint[i];
	}
	Eigen::Vector3f B = a.partialPivLu().solve(b);


	Eigen::VectorXf Thetas = jacobianTranspose * B;
	for (int i = 0; i < 7; i++)
	{
		thetas[i] = Thetas[i] * 180.0 / PI;
	}
}

mat4 IKSim::XDeriv(double theta)
{
	mat4 Deriv = mat4(1.0);
	Deriv[1][1] = -sin(glm::radians((float)theta));
	Deriv[2][2] = -sin(glm::radians((float)theta));
	Deriv[1][2] = cos(glm::radians((float)theta));
	Deriv[2][1] = -cos(glm::radians((float)theta));
	Deriv[0][0] = 0.0;
	Deriv[3][3] = 0.0;
	return Deriv;
}

mat4 IKSim::YDeriv(double theta)
{
	mat4 Deriv = mat4(1.0);
	Deriv[0][0] = -sin(glm::radians((float)theta));
	Deriv[2][2] = -sin(glm::radians((float)theta));
	Deriv[0][2] = -cos(glm::radians((float)theta));
	Deriv[2][0] = cos(glm::radians((float)theta));
	Deriv[1][1] = 0.0;
	Deriv[3][3] = 0.0;
	return Deriv;
}

mat4 IKSim::ZDeriv(double theta)
{
	mat4 Deriv = mat4(1.0);
	Deriv[0][0] = -sin(glm::radians((float)theta));
	Deriv[1][1] = -sin(glm::radians((float)theta));
	Deriv[0][1] = cos(glm::radians((float)theta));
	Deriv[1][0] = -cos(glm::radians((float)theta));
	Deriv[2][2] = 0.0;
	Deriv[3][3] = 0.0;
	return Deriv;
}
