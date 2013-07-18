// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.



#include "Shoot3DriveBackOverDiscs.h"
#include "AutoFire.h"
#include "AutoShooter.h"
#include "AutoStop.h"
#include "DropPickup.h"
#include "RaisePickup.h"
#include "DriveBack.h"


Shoot3DriveBackOverDiscs::Shoot3DriveBackOverDiscs(bool startLeftSidePyramid) {
	
	int num = 1;
	if (startLeftSidePyramid)
	{
		num = -num;
	}
	
	AddSequential (new DropPickup());
	AddSequential (new AutoShooter());
	AddSequential (new AutoFire());
	AddSequential (new AutoFire());
	AddSequential (new AutoFire());

	AddSequential (new RaisePickup());
	AddSequential (new DriveBack(.7, 50*num, 20*num, 100, startLeftSidePyramid));
	AddSequential (new AutoStop(.25));
	
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