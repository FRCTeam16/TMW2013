// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Shooter.h"
#include "../Robotmap.h"
#include "math.h"
#include "../Commands/ShooterStop.h"
#include "../Commands/ShooterRun.h"
Shooter::Shooter() : Subsystem("Shooter") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	wheelShooterEntry = RobotMap::shooterWheelShooterEntry;
	wheelShooterExit = RobotMap::shooterWheelShooterExit;
	shooterAnglePos = RobotMap::shooterShooterAnglePos;
	shooterAngleSteer = RobotMap::shooterShooterAngleSteer;
	shooterAngle = RobotMap::shooterShooterAngle;
	trigger = RobotMap::shooterTrigger;
	triggerStop = RobotMap::shooterTriggerStop;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	runtoggle = true;
	entryset = 0;
	exitset = 0;
	entryvolt = 0;
	exitvolt = 0;
	prevAngle = 0;
	shutoffTimer = GetClock() + 3;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void Shooter::RunAtOutput() {
	
	entryset = entryset + (entryvolt - wheelShooterEntry->GetOutputVoltage())/12;
	exitset = exitset + (exitvolt - wheelShooterExit->GetOutputVoltage())/12;
			
	wheelShooterEntry->Set(entryset);
	wheelShooterExit->Set(exitset);
	
	if(shutoffTimer < GetClock())
		shooterAngle->Disable();
}
void Shooter::SetAngle(int angle) {
	if(prevAngle != angle) {
		shooterAngle->Enable();
		shooterAngle->SetSetpoint(angle - angleOffset);
		shutoffTimer = GetClock() + 5;
		prevAngle = angle;
	}
}
int Shooter::GetCorrectedAngle() {
	return shooterAnglePos->GetAverageValue() - angleOffset;
}
void Shooter::SetSpeeds(float entry, float exit) {
	entryvolt = entry;
	exitvolt = exit;
}
