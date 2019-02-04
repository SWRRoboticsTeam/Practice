/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

//Motor CONFIGURATION
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

task autonomous()

{
	wait1Msec(2000);						  // Robot waits for 2000 milliseconds before executing program

	// Move forward at half power for 1.5 seconds
	motor[rightMotor] = 63;			  // Motor on port2 is run at half (63) power forward
	motor[leftMotor]  = 63;			  // Motor on port3 is run at half (63) power forward
	wait1Msec(1500);				      // Robot runs previous code for 1500 milliseconds before moving on

	// Brake for 1 second
	motor[rightMotor] = 0;				// Motor on port2 is run at half (63) power forward
	motor[leftMotor]  = 0;				// Motor on port3 is run at half (63) power reverse
	wait1Msec(1000);				      // Robot runs previous code for 1000 milliseconds before moving on

	// Move reverse at half power for 1.5 seconds
	motor[rightMotor] = -63;			// Motor on port2 is run at half (63) power forward
	motor[leftMotor]  = -63;			// Motor on port3 is run at half (63) power reverse
	wait1Msec(1500);				      // Robot runs previous code for 1500 milliseconds before moving on

	// Turn left at full power for 0.75 seconds
	motor[rightMotor] = 127;			// Motor on port2 is run at full (127) power forward
	motor[leftMotor]  = -127;		  // Motor on port3 is run at full (-127) power reverse
	wait1Msec(750);					      // Robot runs previous code for 750 milliseconds before moving on
}													      // Program ends, and the robot stops

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

task usercontrol()
{
  // User control code here, inside the loop
	while (1 == 1)									  //Creates and infinite loop
	{
		motor[port2] = vexRT(Ch2);		  //The right motor is set to equal the value transmitted by Ch2 (y-axis of the right joystick)
		motor[port3] = vexRT(Ch3);		  //The left motor is set to equal the value transmitted by Ch3 (y-axis of the left joystick)
	}

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
