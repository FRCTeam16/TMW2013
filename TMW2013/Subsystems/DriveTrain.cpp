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
	frontLeftDrive = RobotMap::driveTrainFrontLeftDrive;
	frontRightDrive = RobotMap::driveTrainFrontRightDrive;
	rearLeftDrive = RobotMap::driveTrainRearLeftDrive;
	rearRightDrive = RobotMap::driveTrainRearRightDrive;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new SteerDrive());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	driveFront = true;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrain::SetWheelbase(float w, float x, float y) {
	W=w;
	X=x;
	Y=y;
}
void DriveTrain::SetMaxSpeed(float MaxSpeed) {
	MaxSpeed = maxspeed;
}
void DriveTrain::SetGyroReference(){
	gyroreference = gyro.GetAngle();
}
void DriveTrain::SetOffsets(float FLOff, float FROff, float RLOff, float RROff) {
	FLOffset = FLOff;
	FROffset = FROff;
	RLOffset = RLOff;
	RROffset = RROff;
}
void DriveTrain::ToggleFrontBack(){
	driveFront = !driveFront;
}
void DriveTrain::Crab(float radian, float speed) {
	
		position = 512 + 512/pi*radian; //converts radians to counts for encoders
			
		//Set Steering PID Setpoints
		if (fabs(frontLeftPos->GetAverageValue() - position) > 256) {
			speed = -speed;
			if(position >= 512)
				position = position - 512;
			else
				position = position + 512;
		}
		
		
		SetSteerSetpoint(position, position, position, position);
		SetDriveSpeed(speed, -speed, speed, -speed);
}
void DriveTrain::Steer(float radian, float speed, float a) {
	
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
	SetDriveSpeed(-FLRatio*speed, FRRatio*speed, -RLRatio*speed, RRRatio*speed);
	
	//Set Steering PID Setpoints
	float FLSetPoint = (256 + 512/pi*thetaFL);
	float FRSetPoint = (256 + 512/pi*thetaFR);
	float RLSetPoint = (256 + 512/pi*thetaRL);
	float RRSetPoint = (256 + 512/pi*thetaRR);
	
	SetSteerSetpoint(FLSetPoint, FRSetPoint, RLSetPoint, RRSetPoint);
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
void DriveTrain::SetSteerSetpoint(float FLSetPoint, float FRSetPoint, float RLSetPoint, float RRSetPoint)
{	
	if(driveFront) {
		
		if (FLSetPoint + FLOffset < 0)
		{
			frontLeft->SetSetpoint(FLSetPoint + FLOffset + 1024);
		}
		else if (FLSetPoint + FLOffset > 1024)
		{
			frontLeft->SetSetpoint(FLSetPoint + FLOffset - 1024);
		}
		else
		{
			frontLeft->SetSetpoint(FLSetPoint + FLOffset);
		}
		
		if (FRSetPoint + FROffset < 0)
		{
			frontRight->SetSetpoint(FRSetPoint + FROffset + 1024);
		}
		else if (FRSetPoint + FROffset > 1024)
		{
			frontRight->SetSetpoint(FRSetPoint + FROffset - 1024);
		}
		else
		{
			frontRight->SetSetpoint(FRSetPoint + FROffset);
		}
		
		if (RLSetPoint + RLOffset < 0)
		{
			rearLeft->SetSetpoint(RLSetPoint + RLOffset + 1024);
		}
		else if (RLSetPoint + RLOffset > 1024)
		{
			rearLeft->SetSetpoint(RLSetPoint + RLOffset - 1024);
		}
		else
		{
			rearLeft->SetSetpoint(RLSetPoint + RLOffset);
		}
		
		if (RRSetPoint + RROffset < 0)
		{
			rearRight->SetSetpoint(RRSetPoint + RROffset + 1024);
		}
		else if (RRSetPoint + RROffset > 1024)
		{
			rearRight->SetSetpoint(RRSetPoint + RROffset - 1024);
		}
		else
		{
			rearRight->SetSetpoint(RRSetPoint + RROffset);
		}
	}
	
	else {
		//FLWheel
		if (RRSetPoint + FLOffset < 0)
		{
			frontLeft->SetSetpoint(RRSetPoint + FLOffset + 1024);
		}
		else if (RRSetPoint + FLOffset > 1024)
		{
			frontLeft->SetSetpoint(RRSetPoint + FLOffset - 1024);
		}
		else
		{
			frontLeft->SetSetpoint(RRSetPoint + FLOffset);
		}
		
		//FRWheel
		if (RLSetPoint + FROffset < 0)
		{
			frontRight->SetSetpoint(RLSetPoint + FROffset + 1024);
		}
		else if (RLSetPoint + FROffset > 1024)
		{
			frontRight->SetSetpoint(RLSetPoint + FROffset - 1024);
		}
		else
		{
			frontRight->SetSetpoint(RLSetPoint + FROffset);
		}
		
		//RLWheel
		if (FRSetPoint + RLOffset < 0)
		{
			rearLeft->SetSetpoint(FRSetPoint + RLOffset + 1024);
		}
		else if (FRSetPoint + RLOffset > 1024)
		{
			rearLeft->SetSetpoint(FRSetPoint + RLOffset - 1024);
		}
		else
		{
			rearLeft->SetSetpoint(FRSetPoint + RLOffset);
		}
		
		//RRWheel
		if (FLSetPoint + RROffset < 0)
		{
			rearRight->SetSetpoint(FLSetPoint + RROffset + 1024);
		}
		else if (FLSetPoint + RROffset > 1024)
		{
			rearRight->SetSetpoint(FLSetPoint + RROffset - 1024);
		}
		else
		{
			rearRight->SetSetpoint(FLSetPoint + RROffset);
		}		
	}
}
void DriveTrain::SetDriveSpeed(float FLSpeed, float FRSpeed, float RLSpeed, float RRSpeed) {
	if(driveFront) {
		frontLeftDrive->Set(FLSpeed);
		frontRightDrive->Set(FRSpeed);
		rearLeftDrive->Set(RLSpeed);
		rearRightDrive->Set(RRSpeed);
	}
	else {
		frontLeftDrive->Set(RRSpeed);
		frontRightDrive->Set(RLSpeed);
		rearLeftDrive->Set(FRSpeed);
		rearRightDrive->Set(FLSpeed);
	}
}
void DriveTrain::Pivot(float twistinput, float speedinput)
{
	
	robotangle = (gyro.GetAngle() - gyroreference)*2*pi/180;
	
	radius = sqrt(pow(Y,2)/4+pow(X,2)/4);
	
	FLWP = pi + atan(Y/X);
	FRWP = pi - atan(Y/X);
	RRWP = atan(W/X);
	RLWP = 2*pi - atan(W/X);
	
	if(fabs(twistinput) + fabs(speedinput) < 1)
		{
		velocity = maxspeed*speedinput;
		angularvelocity = maxspeed*twistinput/radius;
		}
	else
		{
		velocity = maxspeed*speedinput/(fabs(twistinput)+fabs(speedinput));
		angularvelocity = maxspeed*twistinput/(radius*(fabs(twistinput)+fabs(speedinput)));
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
			
	FLXVel = velocity-radius*angularvelocity*sin(FLPos);		
	FRXVel = velocity-radius*angularvelocity*sin(FRPos);
	RRXVel = velocity-radius*angularvelocity*sin(RRPos);
	RLXVel = velocity-radius*angularvelocity*sin(RLPos);
		
	FLYVel = radius*angularvelocity*cos(robotangle+FLWP);
	FRYVel = radius*angularvelocity*cos(robotangle+FRWP);
	RRYVel = radius*angularvelocity*cos(robotangle+RRWP);
	RLYVel = radius*angularvelocity*cos(robotangle+RLWP);
	
	FLVel = sqrt(pow(FLXVel,2)+pow(FLYVel,2));
	FRVel = sqrt(pow(FRXVel,2)+pow(FRYVel,2));
	RLVel = sqrt(pow(RLXVel,2)+pow(RLYVel,2));
	RRVel = sqrt(pow(RRXVel,2)+pow(RRYVel,2));
		 
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
			thetaFL = 2*pi - robotangle + deltaFL + 2*pi;
		else
			thetaFL = 2*pi - robotangle + deltaFL;
		
	if(2*pi - robotangle + deltaFR > 2*pi)
		thetaFR = 2*pi - robotangle + deltaFR - 2*pi;
	else if(2*pi - robotangle + deltaFR < 0)
			thetaFR = 2*pi - robotangle + deltaFR + 2*pi;
		else
			thetaFR = 2*pi - robotangle + deltaFR;
	if(2*pi - robotangle + deltaRR > 2*pi)
		thetaRR = 2*pi - robotangle + deltaRR - 2*pi;
	else if(2*pi - robotangle + deltaRR < 0)
			thetaRR = 2*pi - robotangle + deltaRR + 2*pi;
		else
			thetaRR = 2*pi - robotangle + deltaRR;
	if(2*pi - robotangle + deltaRL > 2*pi)
		thetaRL = 2*pi - robotangle + deltaRL - 2*pi;
	else if(2*pi - robotangle + deltaRL < 0)
			thetaRL = 2*pi - robotangle + deltaRL + 2*pi;
		else
			thetaRL = 2*pi - robotangle + deltaRL;
	
	frontLeft->SetSetpoint(floor(512/pi*thetaFL));
	frontRight->SetSetpoint(floor(512/pi*thetaFR));
	rearLeft->SetSetpoint(floor(512/pi*thetaRL));
	rearRight->SetSetpoint(floor(512/pi*thetaRR));
	
}
void DriveTrain::CurrentLimit(){
	float currentlimit = 100;
	float currenttimeout = 1.5;
	float timeoutreset = 1.5;
	if(frontLeft->IsEnabled() && frontLeftSteer->GetOutputCurrent() > currentlimit){
		if(FLSOTimer < GetClock()){
			FLSOTimer = GetClock()+currenttimeout;
		}
		else{
			frontLeft->Disable();
			FLSOTimer = GetClock() + timeoutreset;
			}
	}
	
	if(!frontLeft->IsEnabled() && FLSOTimer > GetClock())
		frontLeft->Enable();
	
	if(frontRight->IsEnabled() && frontRightSteer->GetOutputCurrent() > currentlimit){
		if(FRSOTimer < GetClock()){
			FRSOTimer = GetClock()+currenttimeout;
		}
		else{
			frontRight->Disable();
			FRSOTimer = GetClock() + timeoutreset;
			}
	}
	
	if(!frontRight->IsEnabled() && FRSOTimer > GetClock())
		frontRight->Enable();
	
	if(rearRight->IsEnabled() && rearRightSteer->GetOutputCurrent() > currentlimit){
		if(RRSOTimer < GetClock()){
			RRSOTimer = GetClock()+currenttimeout;
		}
		else{
			rearRight->Disable();
			RRSOTimer = GetClock() + timeoutreset;
			}
	}
	
	if(!rearRight->IsEnabled() && RLSOTimer > GetClock())
		rearRight->Enable();
	
	if(rearLeft->IsEnabled() && rearLeftSteer->GetOutputCurrent() > currentlimit){
		if(RLSOTimer < GetClock()){
			RLSOTimer = GetClock()+currenttimeout;
		}
		else{
			rearLeft->Disable();
			RLSOTimer = GetClock() + timeoutreset;
			}
	}
	
	if(!rearLeft->IsEnabled() && RLSOTimer > GetClock())
		rearLeft->Enable();
		
}
