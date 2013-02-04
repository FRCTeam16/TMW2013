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
Shooter::Shooter() : Subsystem("Shooter") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	wheelShooterEntry = RobotMap::shooterWheelShooterEntry;
	wheelShooterExit = RobotMap::shooterWheelShooterExit;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new ShooterStop());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	runtoggle = true;
	entryset = 0;
	exitset = 0;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void Shooter::ToggleRun() {
	if (runtoggle) 
		runtoggle = false;
	else {
		runtoggle = true;
		entryset = 0;
		exitset = 0;
	}
;
	
}
void Shooter::RunAtOutput(float entry, float exit) {

	
	entryset = entryset + (entry - wheelShooterEntry->GetOutputVoltage())/12;
	exitset = exitset + (exit - wheelShooterExit->GetOutputVoltage())/12;
			
	wheelShooterEntry->Set(entryset);
	wheelShooterExit->Set(exitset);

	SmartDashboard::PutNumber("EntrySet",entryset);
	SmartDashboard::PutNumber("ExitSet",exitset);
	
	SmartDashboard::PutNumber("EntryVoltage", wheelShooterEntry->GetOutputVoltage());
	SmartDashboard::PutNumber("ExitVoltage", wheelShooterExit->GetOutputVoltage());
	
	SmartDashboard::PutNumber("EntryCurrent", wheelShooterEntry->GetOutputCurrent());
	SmartDashboard::PutNumber("ExitCurrent", wheelShooterExit->GetOutputCurrent());

}
