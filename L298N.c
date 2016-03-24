#include <reg52.h>
#include "L298N.h"

///////////Function/////////////
void Go()
{
	MotorOneLeft = 1;
	MotorOneRight =	0;
	MotorTwoLeft = 0;
	MotorTwoRight =	1;	
}

void Back()
{
	MotorOneLeft = 0;
	MotorOneRight =	1;
	MotorTwoLeft = 1;
	MotorTwoRight =	0;
}

void Stop()
{
	MotorOneLeft = 0;
	MotorOneRight =	0;
	MotorTwoLeft = 0;
	MotorTwoRight =	0;	
}

void SStop()
{
	MotorOneLeft = 1;
	MotorOneRight =	1;
	MotorTwoLeft = 1;
	MotorTwoRight =	1;
}

void Turn_Left()
{
	MotorOneLeft = 0;
	MotorOneRight =	1;
	MotorTwoLeft = 0;
	MotorTwoRight =	1;

}

void Turn_Right()
{
	MotorOneLeft = 1;
	MotorOneRight =	0;
	MotorTwoLeft = 1;
	MotorTwoRight =	0;
}

				  

