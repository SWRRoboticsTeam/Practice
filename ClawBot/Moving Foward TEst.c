#pragma config(Motor,  port2,           leftMotor,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port9,           rightMotor,    tmotorVex393_MC29, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{


setMotor(leftMotor, 127);
setMotor(rightMotor, 127);
wait1Msec(3000);

}