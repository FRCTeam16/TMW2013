// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Fire.h"
Fire::Fire() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Prefs = Preferences::GetInstance();
}
// Called just before this Command runs the first time
void Fire::Initialize() {
	SetTimeout(Prefs->GetFloat("TriggerTime",.6));
}
// Called repeatedly when this Command is scheduled to run
void Fire::Execute() {
	Robot::shooter->trigger->Set(Relay::kForward);
	Robot::shooter->shooterAngle->SetSetpoint(Prefs->GetInt("ShooterAngleSetpoint",350));
	Robot::shooter->RunAtOutput(Prefs->GetFloat("EntrySpeed",0),Prefs->GetFloat("ExitSpeed",0));
}
// Make this return true when this Command no longer needs to run execute()
bool Fire::IsFinished() {
	return IsTimedOut();
}
// Called once after isFinished returns true
void Fire::End() {
	Robot::shooter->trigger->Set(Relay::kOff);
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Fire::Interrupted() {
}