// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "DriveTrain.h"
#include "../Robotmap.h"
#include "../Commands/CrabDrive.h"
#include "../Commands/SteerDrive.h"
DriveTrain::DriveTrain(): 
Subsystem("DriveTrain"),
gyroChannel(1),
gyro(&gyroChannel)
{
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	frontRightPos = RobotMap::driveTrainFrontRightPos;
	frontRightSteer = RobotMap::driveTrainFrontRightSteer;
	frontRight = RobotMap::driveTrainFrontRight;
	frontLeftPos = RobotMap::driveTrainFrontLeftPos;
	frontLeftSteer = RobotMap::driveTrainFrontLeftSteer;
	frontLeft = RobotMap::driveTrainFrontLeft;
	rearRightPos = RobotMap::driveTrainRearRightPos;
	rearRightSteer = RobotMap::driveTrainRearRightSteer;
	rearRight = RobotMap::driveTrainRearRight;
	rearLeftPos = RobotMap::driveTrainRearLeftPos;
	rearLeftSteer = RobotMap::driveTrainRearLeftSteer;
	rearLeft = RobotMap::driveTrainRearLeft;
	frontRightDrive = RobotMap::driveTrainFrontRightDrive;
	frontLeftDrive = RobotMap::driveTrainFrontLeftDrive;
	rearRightDrive = RobotMap::driveTrainRearRightDrive;
	rearLeftDrive = RobotMap::driveTrainRearLeftDrive;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	maxspeed = 100;
}
    
void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new SteerDrive());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrain::SetWheelbase(float w, float x, float y) {
	W=w;
	X=x;
	Y=y;
}
void DriveTrain::SetGyroReference(){
	gyroreference = gyro.GetAngle();
}
void DriveTrain::Crab(float radian, float speed) {
	
		position = 768 - 512/pi*radian; //converts radians to counts for encoders
				
		//Set Steering PID Setpoints
		frontLeft->SetSetpoint(position);
		frontRight->SetSetpoint(position);
		rearLeft->SetSetpoint(position);
		rearRight->SetSetpoint(position);
		
		//Set drive speeds
		frontLeftDrive->Set(-speed);
		frontRightDrive->Set(Robot::oi->getDriverJoystick()->GetY());
		rearLeftDrive->Set(-Robot::oi->getDriverJoystick()->GetY());
		rearRightDrive->Set(Robot::oi->getDriverJoystick()->GetY());
}
void DriveTrain::Steer(float radian, float speed, float a) {
	
	SmartDashboard::PutNumber("Gyro", (float)gyro.GetAngle());
	
	A=a;
	
	thetaRC = pi - radian;  //convert steering angle to rear center wheel angle
	
	if(thetaRC != pi / 2)	//If we are not driving straight forward...
	{
		if(thetaRC < pi / 2)	//Right Turn
		{
			this->RightTurn4Wheels();
		}
		else if(thetaRC > pi / 2)	//Left Turn
		{
			this->LeftTurn4Wheels();
		}
	}
	else	//thetaRC = pi / 2
	{
		thetaFL = pi / 2;
		thetaFR = pi / 2;
		thetaRL = pi / 2;
		thetaRR = pi / 2;
		FLRatio = 1;
		FRRatio = 1;
		RLRatio = 1;
		RRRatio = 1;
	}
	//Solve for fastest wheel speed
	double speedarray[] = {fabs(FL), fabs(FR), fabs(RL), fabs(RR)};
		
	 int length = 4;
     double maxspeed = speedarray[0];
     for(int i = 1; i < length; i++)
     {
          if(speedarray[i] > maxspeed)
                maxspeed = speedarray[i];
     }
		 
	//Set ratios based on maximum wheel speed
	FLRatio = FL/maxspeed;
	FRRatio = FR/maxspeed;
	RLRatio = RL/maxspeed;
	RRRatio = RR/maxspeed;
	
	//Set drive speeds
	frontLeftDrive->Set(-FLRatio*speed);
	frontRightDrive->Set(FRRatio*speed);
	rearLeftDrive->Set(-RLRatio*speed);
	rearRightDrive->Set(RRRatio*speed);
	
	//Set Steering PID Setpoints
	frontLeft->SetSetpoint(768 - 512/pi*thetaFL);
	frontRight->SetSetpoint(768 - 512/pi*thetaFR);
	rearLeft->SetSetpoint(768 - 512/pi*thetaRL);
	rearRight->SetSetpoint(768 - 512/pi*thetaRR);
}
void DriveTrain::LeftTurn4Wheels()
{
	Z = ((A * X) * tan(pi - thetaRC));				//pi was subtracted out of this earlier
	
	thetaRL = pi - atan((Z - W) / (A * X));
	thetaRR = pi - atan((Z + W) / (A * X));
	thetaFR = pi / 2;
	thetaFL = pi / 2;
	
	if(A != 1)
	{
		thetaFL = atan((Z - Y) / ((1 - A) * X));	//These are identical for right and left turns
		thetaFR = atan((Z + Y) / ((1 - A) * X));	//These are identical for right and left turns
	}
	//Solve for radii (wheel speed)
	FL = (Z - Y) / sin(thetaFL);
	FR = (Z + Y) / sin(thetaFR);
	RL = (Z - W) / sin(pi - thetaRL);
	RR = (Z + W) / sin(pi - thetaRR);
}
void DriveTrain::RightTurn4Wheels()
{	
	Z = ((A * X) * tan(thetaRC));				//pi was subtracted out of this earlier
	
	thetaRL = atan((Z + W) / (A * X));
	thetaRR = atan((Z - W) / (A * X));
	thetaFR = pi / 2;
	thetaFL = pi / 2;
	
	if(A != 1)
	{
		thetaFR = pi - atan((Z - Y) / ((1 - A) * X));	//These are identical for right and left turns
		thetaFL = pi - atan((Z + Y) / ((1 - A) * X));	//These are identical for right and left turns
	}
	
	FL = (Z + Y) / sin(pi - thetaFL);
	FR = (Z - Y) / sin(pi - thetaFR);
	RL = (Z + W) / sin(thetaRL);
	RR = (Z - W) / sin(thetaRR);
}
void DriveTrain::Pivot(float twistinput, float speedinput)
{
	
	robotangle = gyro.GetAngle() - gyroreference;
	
	diagonal = sqrt(pow(Y,2)/4+pow(X,2)/4);
	
	FLWP = pi + atan(Y/X);
	FRWP = pi - atan(Y/X);
	RRWP = atan(W/X);
	RLWP = 2*pi - atan(W/X);
	
	if(fabs(twistinput) + fabs(speedinput) < 1)
		{
		velocity = maxspeed*speedinput;
		angularvelocity = maxspeed*speedinput;
		}
	else
		{
		velocity = maxspeed*speedinput/(fabs(twistinput)+fabs(speedinput));
		angularvelocity = maxspeed*speedinput/(fabs(twistinput)+fabs(speedinput));
		}
	
	if(FLWP + robotangle > 2*pi)
		FLPos = FLWP + robotangle -2*pi;
	else if(FLWP + robotangle < 0)
			FLPos = FLWP + robotangle + 2*pi;
		else
			FLPos = FLWP + robotangle;
	
	if(FRWP + robotangle > 2*pi)
		FRPos = FRWP + robotangle -2*pi;
	else if(FRWP + robotangle < 0)
			FRPos = FRWP + robotangle + 2*pi;
		else
			FLPos = FLWP + robotangle;
	
	if(RRWP + robotangle > 2*pi)
		RRPos = RRWP + robotangle -2*pi;
	else if(RRWP + robotangle < 0)
			RRPos = RRWP + robotangle + 2*pi;
		else
			RRPos = RRWP + robotangle;
	
	if(RLWP + robotangle > 2*pi)
		RLPos = RLWP + robotangle -2*pi;
	else if(RLWP + robotangle < 0)
			RLPos = RLWP + robotangle + 2*pi;
		else
			RLPos = RLWP + robotangle;
			
	FLXVel = velocity-diagonal*angularvelocity*sin(FLPos);		
	FRXVel = velocity-diagonal*angularvelocity*sin(FRPos);
	RRXVel = velocity-diagonal*angularvelocity*sin(RRPos);
	RLXVel = velocity-diagonal*angularvelocity*sin(RLPos);
		
	FLYVel = diagonal*angularvelocity*cos(robotangle+FLWP);
	FRYVel = diagonal*angularvelocity*cos(robotangle+FRWP);
	RRYVel = diagonal*angularvelocity*cos(robotangle+RRWP);
	RLYVel = diagonal*angularvelocity*cos(robotangle+RLWP);
	
	//Solve for fastest wheel speed
	double speedarray[] = {fabs(FLVel), fabs(FRVel), fabs(RLVel), fabs(RRVel)};
		
	 int length = 4;
     double maxspeed = speedarray[0];
     for(int i = 1; i < length; i++)
     {
          if(speedarray[i] > maxspeed)
                maxspeed = speedarray[i];
     }
		 
	//Set ratios based on maximum wheel speed
	FLRatio = FL/maxspeed;
	FRRatio = FR/maxspeed;
	RLRatio = RL/maxspeed;
	RRRatio = RR/maxspeed;
	
	//Set drive speeds
	frontLeftDrive->Set(-FLRatio);
	frontRightDrive->Set(FRRatio);
	rearLeftDrive->Set(-RLRatio);
	rearRightDrive->Set(RRRatio);
	
	SmartDashboard::PutNumber("FLRatio", FLRatio);
	SmartDashboard::PutNumber("FRRatio", FRRatio);
	SmartDashboard::PutNumber("RLRatio", RLRatio);
	SmartDashboard::PutNumber("RRRatio", RRRatio);
	
	
	if(FLXVel <= 0)
		if(FLPos < pi/2)
			deltaFL = atan(FLYVel/FLXVel) + pi;
		else
			deltaFL = atan(FLYVel/FLXVel) - pi;
	else
		deltaFL = atan(FLYVel/FLXVel);
	
	if(FRXVel <= 0)
		if(FRPos < pi/2)
			deltaFR = atan(FRYVel/FRXVel) + pi;
		else
			deltaFR = atan(FRYVel/FRXVel) - pi;
	else
		deltaFR = atan(FRYVel/FRXVel);
		
	if(RRXVel <= 0)
		if(RRPos < pi/2)
			deltaRR = atan(RRYVel/RRXVel) + pi;
		else
			deltaRR = atan(RRYVel/RRXVel) - pi;
	else
		deltaRR = atan(RRYVel/RRXVel);
	if(RLXVel <= 0)
		if(RLPos < pi/2)
			deltaRL = atan(RLYVel/RLXVel) + pi;
		else
			deltaRL = atan(RLYVel/RLXVel) - pi;
	else
		deltaRL = atan(RLYVel/RLXVel);
		
	
	if(2*pi - robotangle + deltaFL > 2*pi)
		thetaFL = 2*pi - robotangle + deltaFL - 2*pi;
	else if(2*pi - robotangle + deltaFL < 0)
			thetaFL = 2*pi - robotangle + deltaFL - 2*pi;
	else
		thetaFL = 2*pi - robotangle + deltaFL;
		
	if(2*pi - robotangle + deltaFR > 2*pi)
		thetaFR = 2*pi - robotangle + deltaFR - 2*pi;
	else if(2*pi - robotangle + deltaFR < 0)
			thetaFR = 2*pi - robotangle + deltaFR - 2*pi;
	else
		thetaFR = 2*pi - robotangle + deltaFR;
	if(2*pi - robotangle + deltaRR > 2*pi)
		thetaRR = 2*pi - robotangle + deltaRR - 2*pi;
	else if(2*pi - robotangle + deltaRR < 0)
			thetaRR = 2*pi - robotangle + deltaRR - 2*pi;
	else
		thetaRR = 2*pi - robotangle + deltaRR;
	if(2*pi - robotangle + deltaRL > 2*pi)
		thetaRL = 2*pi - robotangle + deltaRL - 2*pi;
	else if(2*pi - robotangle + deltaRL < 0)
			thetaRL = 2*pi - robotangle + deltaRL - 2*pi;
	else
		thetaRL = 2*pi - robotangle + deltaRL;
	
	SmartDashboard::PutNumber("FLPosSet", 512/pi*thetaFL);
	SmartDashboard::PutNumber("FRPosSet", 512/pi*thetaFR);
	SmartDashboard::PutNumber("RLPosSet", 512/pi*thetaRL);
	SmartDashboard::PutNumber("RRPosSet", 512/pi*thetaRR);
	
	/*
	//Set Steering PID Setpoints  ----THIS NEEDS TO BE DEBUGGED... NOT SURE WHERE 0RAD IS FOR THIS MATH
	frontLeft->SetSetpoint(512/pi*thetaFL);
	frontRight->SetSetpoint(512/pi*thetaFR);
	rearLeft->SetSetpoint(512/pi*thetaRL);
	rearRight->SetSetpoint(512/pi*thetaRR);
	*/
}
