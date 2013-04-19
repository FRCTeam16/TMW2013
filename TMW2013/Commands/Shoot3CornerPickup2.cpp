// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.



#include "Shoot3CornerPickup2.h"
#include "AutoFire.h"
#include "Drive.h"
#include "DriveToDiscs.h"
#include "TurnWheels.h"
#include "TurnRobot.h"
#include "ShooterInMiddle.h"
#include "AutoShooter.h"
#include "ResetWheelCounter.h"
#include "DriveToPyramid.h"
#include "DriveBack.h"
#include "FollowLine.h"
#include "AutoStop.h"
#include "AutoShooter2.h"


Shoot3CornerPickup2::Shoot3CornerPickup2() {
	AddSequential (new AutoShooter());
	AddSequential (new AutoFire());
	AddSequential (new AutoFire());
	AddSequential (new AutoFire());

 /*	AddSequential (new DriveBack(.45, 20, 112, 5));
 	AddSequential (new AutoStop(.5));
 	AddSequential (new FollowLine(.3, 0, 112, 2));
 	AddSequential (new Drive(.4, 120, 20, 1)); // Left Side Center Line 2 pt
*/
 	AddSequential (new DriveBack(.40, -20, -112, 5));
	AddSequential (new AutoStop(.5));
	AddSequential (new FollowLine(.3, 0, -112, 2));
 	AddSequential (new Drive(.4, -130, -20, .7)); // Left Side Center Line 2 pt
 	
 	AddSequential (new AutoShooter2());
 	AddSequential (new AutoFire());
	AddSequential (new AutoFire());
	AddSequential (new AutoFire());
	AddSequential (new AutoFire());
 	
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
