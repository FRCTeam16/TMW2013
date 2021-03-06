// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "AutoFire.h"
AutoFire::AutoFire() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void AutoFire::Initialize() {
	SetTimeout(3);
	fired = false;
	entrySpeed = Robot::shooter->GetEntrySpeed();
	exitSpeed = Robot::shooter->GetExitSpeed();
	notready = false;
	if(exitSpeed >= 0 || entrySpeed >=0)
		notready = true;
	prevFireTime = Robot::shooter->GetFireTime();
}
// Called repeatedly when this Command is scheduled to run
void AutoFire::Execute() {
	if(!notready && Robot::shooter->IsShooterReady()) {
		if(!fired){
			Robot::shooter->trigger->Set(Relay::kForward);
			fired = true;
			Robot::shooter->SetFireTimer();
		}
	}
	
	if(Robot::shooter->trigger->Get() == 0 && fired == true && prevFireTime == Robot::shooter->GetFireTime())
		Initialize();
}
// Make this return true when this Command no longer needs to run execute()
bool AutoFire::IsFinished() {
	return (Robot::shooter->trigger->Get() == 0 && fired == true && prevFireTime != Robot::shooter->GetFireTime()) || notready;	
}
// Called once after isFinished returns true
void AutoFire::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoFire::Interrupted() {
}
