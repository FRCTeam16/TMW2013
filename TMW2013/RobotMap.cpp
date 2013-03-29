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
SpeedController* RobotMap::driveTrainFrontLeftDrive = NULL;
SpeedController* RobotMap::driveTrainFrontRightDrive = NULL;
SpeedController* RobotMap::driveTrainRearLeftDrive = NULL;
SpeedController* RobotMap::driveTrainRearRightDrive = NULL;
Gyro* RobotMap::driveTrainGyroscope = NULL;
CANJaguar* RobotMap::shooterWheelShooterEntry = NULL;
CANJaguar* RobotMap::shooterWheelShooterExit = NULL;
AnalogChannel* RobotMap::shooterShooterAnglePos = NULL;
CANJaguar* RobotMap::shooterShooterAngleSteer = NULL;
PIDController* RobotMap::shooterShooterAngle = NULL;
DigitalInput* RobotMap::shooterTriggerStop = NULL;
SpeedController* RobotMap::shooterTrigger = NULL;
AnalogChannel* RobotMap::pickupPickupAngle = NULL;
CANJaguar* RobotMap::pickupPickup = NULL;
SpeedController* RobotMap::climberClimbLeft = NULL;
SpeedController* RobotMap::climberClimbRight = NULL;
CANJaguar* RobotMap::climberAngleLeft = NULL;
CANJaguar* RobotMap::climberAngleRight = NULL;
Encoder* RobotMap::climberClimberDistance = NULL;
DigitalInput* RobotMap::climberExtendLimit = NULL;
DigitalInput* RobotMap::climberRetractLimit = NULL;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();
	driveTrainFrontRightPos = new AnalogChannel(1, 3);
	lw->AddSensor("DriveTrain", "FrontRightPos", driveTrainFrontRightPos);
	
	driveTrainFrontRightSteer = new CANJaguar(7);
	
	
	driveTrainFrontRight = new PIDController(0.01, 0.0, 0.0,/* F: 0.0, */ driveTrainFrontRightPos, driveTrainFrontRightSteer, 0.02);
	lw->AddActuator("DriveTrain", "FrontRight", driveTrainFrontRight);
	driveTrainFrontRight->SetContinuous(true); driveTrainFrontRight->SetAbsoluteTolerance(20.0); 
        driveTrainFrontRight->SetInputRange(0.0, 1023.0);
        driveTrainFrontRight->SetOutputRange(-0.75, 0.75);
	driveTrainFrontLeftPos = new AnalogChannel(1, 2);
	lw->AddSensor("DriveTrain", "FrontLeftPos", driveTrainFrontLeftPos);
	
	driveTrainFrontLeftSteer = new CANJaguar(6);
	
	
	driveTrainFrontLeft = new PIDController(0.01, 0.0, 0.0,/* F: 0.0, */ driveTrainFrontLeftPos, driveTrainFrontLeftSteer, 0.02);
	lw->AddActuator("DriveTrain", "FrontLeft", driveTrainFrontLeft);
	driveTrainFrontLeft->SetContinuous(true); driveTrainFrontLeft->SetAbsoluteTolerance(20.0); 
        driveTrainFrontLeft->SetInputRange(0.0, 1023.0);
        driveTrainFrontLeft->SetOutputRange(-0.75, 0.75);
	driveTrainRearRightPos = new AnalogChannel(1, 5);
	lw->AddSensor("DriveTrain", "RearRightPos", driveTrainRearRightPos);
	
	driveTrainRearRightSteer = new CANJaguar(9);
	
	
	driveTrainRearRight = new PIDController(0.01, 0.0, 0.0,/* F: 0.0, */ driveTrainRearRightPos, driveTrainRearRightSteer, 0.02);
	lw->AddActuator("DriveTrain", "RearRight", driveTrainRearRight);
	driveTrainRearRight->SetContinuous(true); driveTrainRearRight->SetAbsoluteTolerance(20.0); 
        driveTrainRearRight->SetInputRange(0.0, 1023.0);
        driveTrainRearRight->SetOutputRange(-0.75, 0.75);
	driveTrainRearLeftPos = new AnalogChannel(1, 4);
	lw->AddSensor("DriveTrain", "RearLeftPos", driveTrainRearLeftPos);
	
	driveTrainRearLeftSteer = new CANJaguar(8);
	
	
	driveTrainRearLeft = new PIDController(0.01, 0.0, 0.0,/* F: 0.0, */ driveTrainRearLeftPos, driveTrainRearLeftSteer, 0.02);
	lw->AddActuator("DriveTrain", "RearLeft", driveTrainRearLeft);
	driveTrainRearLeft->SetContinuous(true); driveTrainRearLeft->SetAbsoluteTolerance(20.0); 
        driveTrainRearLeft->SetInputRange(0.0, 1023.0);
        driveTrainRearLeft->SetOutputRange(-0.75, 0.75);
	driveTrainFrontLeftDrive = new Victor(1, 1);
	lw->AddActuator("DriveTrain", "FrontLeftDrive", (Victor*) driveTrainFrontLeftDrive);
	
	driveTrainFrontRightDrive = new Victor(1, 2);
	lw->AddActuator("DriveTrain", "FrontRightDrive", (Victor*) driveTrainFrontRightDrive);
	
	driveTrainRearLeftDrive = new Victor(1, 3);
	lw->AddActuator("DriveTrain", "RearLeftDrive", (Victor*) driveTrainRearLeftDrive);
	
	driveTrainRearRightDrive = new Victor(1, 4);
	lw->AddActuator("DriveTrain", "RearRightDrive", (Victor*) driveTrainRearRightDrive);
	
	driveTrainGyroscope = new Gyro(1, 1);
	lw->AddSensor("DriveTrain", "Gyroscope", driveTrainGyroscope);
	driveTrainGyroscope->SetSensitivity(0.007);
	shooterWheelShooterEntry = new CANJaguar(11);
	
	
	shooterWheelShooterExit = new CANJaguar(10);
	
	
	shooterShooterAnglePos = new AnalogChannel(1, 7);
	lw->AddSensor("Shooter", "ShooterAnglePos", shooterShooterAnglePos);
	
	shooterShooterAngleSteer = new CANJaguar(12);
	
	
	shooterShooterAngle = new PIDController(0.1, 0.0, 0.0,/* F: 0.0, */ shooterShooterAnglePos, shooterShooterAngleSteer, 0.02);
	lw->AddActuator("Shooter", "ShooterAngle", shooterShooterAngle);
	shooterShooterAngle->SetContinuous(true); shooterShooterAngle->SetAbsoluteTolerance(2.0); 
        shooterShooterAngle->SetInputRange(0.0, 1023.0);
        shooterShooterAngle->SetOutputRange(-1.0, 1.0);
	shooterTriggerStop = new DigitalInput(1, 5);
	lw->AddSensor("Shooter", "TriggerStop", shooterTriggerStop);
	
	shooterTrigger = new Victor(1, 7);
	lw->AddActuator("Shooter", "Trigger", (Victor*) shooterTrigger);
	
	pickupPickupAngle = new AnalogChannel(1, 6);
	lw->AddSensor("Pickup", "PickupAngle", pickupPickupAngle);
	
	pickupPickup = new CANJaguar(15);
	
	
	climberClimbLeft = new Victor(1, 5);
	lw->AddActuator("Climber", "ClimbLeft", (Victor*) climberClimbLeft);
	
	climberClimbRight = new Victor(1, 6);
	lw->AddActuator("Climber", "ClimbRight", (Victor*) climberClimbRight);
	
	climberAngleLeft = new CANJaguar(13);
	
	
	climberAngleRight = new CANJaguar(14);
	
	
	climberClimberDistance = new Encoder(1, 1, 1, 2, false, Encoder::k1X);
	lw->AddSensor("Climber", "ClimberDistance", climberClimberDistance);
	climberClimberDistance->SetDistancePerPulse(0.00128571);
        climberClimberDistance->SetPIDSourceParameter(Encoder::kDistance);
        climberClimberDistance->Start();
	climberExtendLimit = new DigitalInput(1, 3);
	lw->AddSensor("Climber", "ExtendLimit", climberExtendLimit);
	
	climberRetractLimit = new DigitalInput(1, 4);
	lw->AddSensor("Climber", "RetractLimit", climberRetractLimit);
	
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
