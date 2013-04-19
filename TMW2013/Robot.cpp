// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Robot.h"
#include "Commands/Shoot3FromCorner.h"
#include "Commands/NoneAuto.h"
#include "Commands/Shoot3CornerPickup2.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
DriveTrain* Robot::driveTrain = 0;
Shooter* Robot::shooter = 0;
Pickup* Robot::pickup = 0;
Climber* Robot::climber = 0;
Blocker* Robot::blocker = 0;
OI* Robot::oi = 0;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
TriggerMonitor triggerMonitor;
void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	driveTrain = new DriveTrain();
	shooter = new Shooter();
	pickup = new Pickup();
	climber = new Climber();
	blocker = new Blocker();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi = new OI();
	lw = LiveWindow::GetInstance();
	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new AutonomousCommand();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	
	Prefs = Preferences::GetInstance();
	File = RAWCConstants::getInstance();
	Robot::driveTrain->SetWheelbase(8, 22, 8);
	Robot::driveTrain->SetMaxSpeed(100);
	
	FLOffset = (int)File->getValueForKey("FLOff");
	FROffset = (int)File->getValueForKey("FROff");
	RLOffset = (int)File->getValueForKey("RLOff");
	RROffset = (int)File->getValueForKey("RROff");
	
	Robot::driveTrain->SetOffsets(FLOffset, FROffset, RLOffset, RROffset);
	
	Robot::driveTrain->frontLeftPos->SetAverageBits(256);
	Robot::driveTrain->frontRightPos->SetAverageBits(256);
	Robot::driveTrain->rearLeftPos->SetAverageBits(256);
	Robot::driveTrain->rearRightPos->SetAverageBits(256);
		
	Robot::driveTrain->frontLeft->Enable();
	Robot::driveTrain->frontRight->Enable();
	Robot::driveTrain->rearLeft->Enable();
	Robot::driveTrain->rearRight->Enable();
	Robot::shooter->shooterAngle->Enable();
	
	if(!Prefs->ContainsKey("SteerScaling"))
		Prefs->PutFloat("SteerScaling",1.5);
	if(!Prefs->ContainsKey("EntrySpeed"))
			Prefs->PutFloat("EntrySpeed",-7.5);
	if(!Prefs->ContainsKey("ExitSpeed"))
			Prefs->PutFloat("ExitSpeed",9);
	if(!Prefs->ContainsKey("ShooterAngleSetpoint"))
			Prefs->PutInt("ShooterAngleSetpoint",395);
	
	autoChooser = new SendableChooser();
	autoChooser->AddObject("None", new NoneAuto());
	autoChooser->AddDefault("Shoot3FromCorner", new Shoot3FromCorner());
	autoChooser->AddObject("Shoot3CornerPickup2", new Shoot3CornerPickup2());
	SmartDashboard::PutData("Autonomous Chooser", autoChooser);
		
	Robot::shooter->shooterAngle->SetSetpoint(Robot::shooter->GetCorrectedAngle());
	
	Robot::driveTrain->wheelSpokeCounter->Start();
	Robot::driveTrain->wheelSpokeCounter->Reset();
	
	Robot::climber->comp->Start();
	
	Robot::shooter->trigger->Set(0);
}
	
void Robot::DisabledPeriodic(){
	Scheduler::GetInstance()->Run();
}
void Robot::AutonomousInit() {
	Robot::driveTrain->SetDriveBackFlag(false);
	autonomousCommand = (Command*) autoChooser->GetSelected();
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
	triggerMonitor.Start();
}
	
void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	Robot::shooter->RunAtOutput();
	
}	
void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// this line or comment it out.
	autonomousCommand->Cancel();
	triggerMonitor.Start();
}
void Robot::TeleopPeriodic() {
	if (autonomousCommand != NULL)
		Scheduler::GetInstance()->Run();
		
	Robot::shooter->RunAtOutput();
	
	if(Robot::oi->getDriverJoystick()->GetRawButton(11))
		Robot::driveTrain->wheelSpokeCounter->Reset();
	
	if (Robot::oi->getGamePad()->GetRockerY() > 0.5)
		Robot::shooter->SetAngle(Robot::shooter->GetCorrectedAngle() + 6);
	
	if (Robot::oi->getGamePad()->GetRockerY() < -0.5)
		Robot::shooter->SetAngle(Robot::shooter->GetCorrectedAngle() - 6);
	
	if(Robot::oi->getGamePad()->GetRawButton(5))
		Robot::climber->climb->Set(true);
	else
		Robot::climber->climb->Set(false);
	
	if (Robot::oi->getGamePad()->GetRawButton(6))
		Robot::pickup->pickupLift->Set(DoubleSolenoid::kForward);
	
	if (Robot::oi->getGamePad()->GetRawButton(8))
		Robot::pickup->pickupLift->Set(DoubleSolenoid::kReverse);
	
	Robot::pickup->beaterBar->Set(Robot::oi->getGamePad()->GetLeftY());
	
	Robot::blocker->blockerWinch->Set(Robot::oi->getGamePad()->GetRightY());
}
void Robot::TestPeriodic() {
	lw->Run();
}
START_ROBOT_CLASS(Robot);
