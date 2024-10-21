#pragma once
#include "glfw3.h"




struct Time
{
	static void update_time(double fpsCalcInt = 1.0);



	static GLdouble fps;
	static GLdouble delta_time; // time taken to complete most recent game loop

};