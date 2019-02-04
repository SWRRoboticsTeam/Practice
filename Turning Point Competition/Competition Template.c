#pragma config(Sensor, I2C_1,  rightIME,       sensorNone)
#pragma config(Sensor, I2C_2,  leftIME,        sensorNone)
#pragma config(Sensor, I2C_3,  armIME,         sensorNone)
#pragma config(Motor,  port2,           rightWheel,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightTred,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftTred,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           clawOpen,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           bottomArm,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           topArm,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           leftWheel,     tmotorVex393HighSpeed_MC29, openLoop)

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
	// bDisplayCompetitionStatusOnLcd = false;

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

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  // User control code here, inside the loop

  while (true)
  {

while(1==1){

	//Movement
	motor[leftWheel] = vexRT[Ch3];
	motor[leftTred] = vexRT[Ch3];
	motor[rightWheel] = vexRT[Ch2];
	motor[rightTred] = vexRT[Ch2];

	//Claw & Arm Controls

	if(vexRT[Btn6U]){
	motor[clawOpen] = 127;
}
else if(vexRT[Btn6D]){
	motor[clawOpen] = -127;
}
else{
	motor[clawOpen] = 0;
}

	if(vexRT[Btn5U]){
	motor[topArm] = 127;
	motor[bottomArm] = 127;
}
else if(vexRT[Btn5D]){
	motor[topArm] = -127;
	motor[bottomArm] = -127;
}
else{
	motor[topArm] = 0;
	motor[bottomArm] = 0;
}


}
}
  }
