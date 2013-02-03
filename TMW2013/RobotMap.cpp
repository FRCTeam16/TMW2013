// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
AnalogChannel* RobotMap::driveTrainFrontRightPos = NULL;
CANJaguar* RobotMap::driveTrainFrontRightSteer = NULL;
PIDController* RobotMap::driveTrainFrontRight = NULL;
AnalogChannel* RobotMap::driveTrainFrontLeftPos = NULL;
CANJaguar* RobotMap::driveTrainFrontLeftSteer = NULL;
PIDController* RobotMap::driveTrainFrontLeft = NULL;
AnalogChannel* RobotMap::driveTrainRearRightPos = NULL;
CANJaguar* RobotMap::driveTrainRearRightSteer = NULL;
PIDController* RobotMap::driveTrainRearRight = NULL;
AnalogChannel* RobotMap::driveTrainRearLeftPos = NULL;
CANJaguar* RobotMap::driveTrainRearLeftSteer = NULL;
PIDController* RobotMap::driveTrainRearLeft = NULL;
CANJaguar* RobotMap::driveTrainFrontRightDrive = NULL;
CANJaguar* RobotMap::driveTrainFrontLeftDrive = NULL;
CANJaguar* RobotMap::driveTrainRearRightDrive = NULL;
CANJaguar* RobotMap::driveTrainRearLeftDrive = NULL;
CANJaguar* RobotMap::shooterWheelShooterEntry = NULL;
CANJaguar* RobotMap::shooterWheelShooterExit = NULL;
Servo* RobotMap::pickupServo1 = NULL;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();
	driveTrainFrontRightPos = new AnalogChannel(1, 3);
	lw->AddSensor("DriveTrain", "FrontRightPos", driveTrainFrontRightPos);
	
	driveTrainFrontRightSteer = new CANJaguar(7);
	
	
	driveTrainFrontRight = new PIDController(0.01, 0.0, 0.0,/* F: 0.0, */ driveTrainFrontRightPos, driveTrainFrontRightSteer, 0.02);
	lw->AddActuator("DriveTrain", "FrontRight", driveTrainFrontRight);
	driveTrainFrontRight->SetContinuous(true); driveTrainFrontRight->SetAbsoluteTolerance(0.2); 
        driveTrainFrontRight->SetInputRange(0.0, 1024.0);
        driveTrainFrontRight->SetOutputRange(-1.0, 1.0);
	driveTrainFrontLeftPos = new AnalogChannel(1, 2);
	lw->AddSensor("DriveTrain", "FrontLeftPos", driveTrainFrontLeftPos);
	
	driveTrainFrontLeftSteer = new CANJaguar(6);
	
	
	driveTrainFrontLeft = new PIDController(0.01, 0.0, 0.0,/* F: 0.0, */ driveTrainFrontLeftPos, driveTrainFrontLeftSteer, 0.02);
	lw->AddActuator("DriveTrain", "FrontLeft", driveTrainFrontLeft);
	driveTrainFrontLeft->SetContinuous(true); driveTrainFrontLeft->SetAbsoluteTolerance(0.2); 
        driveTrainFrontLeft->SetInputRange(0.0, 1024.0);
        driveTrainFrontLeft->SetOutputRange(-1.0, 1.0);
	driveTrainRearRightPos = new AnalogChannel(1, 5);
	lw->AddSensor("DriveTrain", "RearRightPos", driveTrainRearRightPos);
	
	driveTrainRearRightSteer = new CANJaguar(9);
	
	
	driveTrainRearRight = new PIDController(0.01, 0.0, 0.0,/* F: 0.0, */ driveTrainRearRightPos, driveTrainRearRightSteer, 0.02);
	lw->AddActuator("DriveTrain", "RearRight", driveTrainRearRight);
	driveTrainRearRight->SetContinuous(true); driveTrainRearRight->SetAbsoluteTolerance(0.2); 
        driveTrainRearRight->SetInputRange(0.0, 1024.0);
        driveTrainRearRight->SetOutputRange(-1.0, 1.0);
	driveTrainRearLeftPos = new AnalogChannel(1, 4);
	lw->AddSensor("DriveTrain", "RearLeftPos", driveTrainRearLeftPos);
	
	driveTrainRearLeftSteer = new CANJaguar(8);
	
	
	driveTrainRearLeft = new PIDController(0.01, 0.0, 0.0,/* F: 0.0, */ driveTrainRearLeftPos, driveTrainRearLeftSteer, 0.02);
	lw->AddActuator("DriveTrain", "RearLeft", driveTrainRearLeft);
	driveTrainRearLeft->SetContinuous(true); driveTrainRearLeft->SetAbsoluteTolerance(0.2); 
        driveTrainRearLeft->SetInputRange(0.0, 1024.0);
        driveTrainRearLeft->SetOutputRange(-1.0, 1.0);
	driveTrainFrontRightDrive = new CANJaguar(3);
	
	
	driveTrainFrontLeftDrive = new CANJaguar(2);
	
	
	driveTrainRearRightDrive = new CANJaguar(5);
	
	
	driveTrainRearLeftDrive = new CANJaguar(4);
	
	
	shooterWheelShooterEntry = new CANJaguar(11);
	
	
	shooterWheelShooterExit = new CANJaguar(10);
	
	
	pickupServo1 = new Servo(1, 1);
	lw->AddActuator("Pickup", "Servo 1", pickupServo1);
	
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
