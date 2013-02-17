// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef CLIMBER_H
#define CLIMBER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class Climber: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	float SOTimer;
	void CurrentLimit();
	
	//Caclulate the angleOffset by fully extending the climber and laying flat on ground.  
	//The expected value is 224.  
	//Subtract the actual from 224 and set to angleOffset in contructor in climber.cpp.
	//Verify that the rollover value isn't within the travel of the climber
	static const int angleOffset = 0;
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	SpeedController* climbLeft;
	SpeedController* climbRight;
	CANJaguar* angleRight;
	CANJaguar* angleLeft;
	AnalogChannel* anglePos;
	PIDController* angle;
	Encoder* climberDistance;
	DigitalInput* extendLimit;
	DigitalInput* retractLimit;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Climber();
	void InitDefaultCommand();
	void SetAngle(int Angle);
	void RunClimber(float speed);
	int GetCorrectedAngle();
};
#endif
