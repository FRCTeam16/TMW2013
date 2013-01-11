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
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
DriveTrain* Robot::driveTrain = 0;
OI* Robot::oi = 0;
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	driveTrain = new DriveTrain();
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
	
	File = RAWCConstants::getInstance();
	 
	FLOffset = File->getValueForKey("FLOff");
	FROffset = File->getValueForKey("FROff");
	RLOffset = File->getValueForKey("RLOff");
	RROffset = File->getValueForKey("RROff");
	
	Robot::driveTrain->frontLeft->SetOffset(335);
	Robot::driveTrain->frontRight->SetOffset(590);
	Robot::driveTrain->rearLeft->SetOffset(512);
	Robot::driveTrain->rearRight->SetOffset(465);
	
	Robot::driveTrain->frontLeftPos->SetAverageBits(256);
	Robot::driveTrain->frontRightPos->SetAverageBits(256);
	Robot::driveTrain->rearLeftPos->SetAverageBits(256);
	Robot::driveTrain->rearRightPos->SetAverageBits(256);
	
//	drivetrain->frontLeft->Enable();
//	drivetrain->frontRight->Enable();
//	drivetrain->rearLeft->Enable();
//	drivetrain->rearRight->Enable();
  }
	
void Robot::DisabledPeriodic(){
	SmartDashboard::PutNumber("FrontLeftPos",Robot::driveTrain->frontLeftPos->GetAverageValue());
	SmartDashboard::PutNumber("FrontRightPos",Robot::driveTrain->frontRightPos->GetAverageValue());
	SmartDashboard::PutNumber("RearLeftPos",Robot::driveTrain->rearLeftPos->GetAverageValue());
	SmartDashboard::PutNumber("RearRightPos",Robot::driveTrain->rearRightPos->GetAverageValue());
	SmartDashboard::PutNumber("SW",Robot::oi->getSteeringWheel());	
}
void Robot::AutonomousInit() {
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
}
	
void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}
	
void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// this line or comment it out.
	autonomousCommand->Cancel();
}
	
void Robot::TeleopPeriodic() {
	if (autonomousCommand != NULL)
		Scheduler::GetInstance()->Run();
}
void Robot::TestPeriodic() {
	lw->Run();
}
START_ROBOT_CLASS(Robot);