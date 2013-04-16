// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#ifndef FOLLOWLINE_H
#define FOLLOWLINE_H


#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "../FollowLineTask.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class FollowLine: public Command {
public:
	FollowLine();
	FollowLine(float speed, float driveangle, float twistangle, float timeout);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float X;
	float Y;
	float TwistAngle;
	float Twist;
	float Timeout;

	
};

#endif