// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "OI.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/CrabDrive.h"
#include "Commands/DriveSide.h"
#include "Commands/DriveStraight.h"
#include "Commands/SetWheelOffsets.h"
#include "Commands/SteerDrive.h"
#include "Commands/TurnRobot.h"
#include "Commands/TurnWheelsSide.h"
#include "Commands/TurnWheelsStraight.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	driverJoystick = new Joystick(1);
	
	wheelOffsetButton = new JoystickButton(driverJoystick, 6);
	wheelOffsetButton->WhenPressed(new SetWheelOffsets());
	trigger = new JoystickButton(driverJoystick, 1);
	trigger->WhileHeld(new CrabDrive());
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
	SmartDashboard::PutData("CrabDrive", new CrabDrive());
	SmartDashboard::PutData("SetWheelOffsets", new SetWheelOffsets());
	SmartDashboard::PutData("TurnWheelsStraight", new TurnWheelsStraight());
	SmartDashboard::PutData("TurnWheelsSide", new TurnWheelsSide());
	SmartDashboard::PutData("TurnRobot", new TurnRobot());
	SmartDashboard::PutData("DriveStraight", new DriveStraight());
	SmartDashboard::PutData("DriveSide", new DriveSide());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
Joystick* OI::getDriverJoystick() {
	return driverJoystick;
}
double OI::getSteeringWheel() {
	return DriverStation::GetInstance()->GetAnalogIn(2);
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
