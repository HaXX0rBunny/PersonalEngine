#include "Time.h"
//#include "Time.h"
//
//float BGFrameRateControllerGetFrameTime()
//{
//
//}
GLdouble Time::fps;
GLdouble Time::delta_time;
void Time::update_time(double fpsCalcInt)
{
	static double sd_preTime = glfwGetTime();
	double d_curTime = glfwGetTime();
	delta_time = d_curTime - sd_preTime;
	sd_preTime = d_curTime;
	
	static double sd_count = 0.0;
	static double sd_startTime = glfwGetTime();

	double elapsed_time = d_curTime - sd_startTime;
	sd_count++;

	fpsCalcInt = (fpsCalcInt < 0.0) ? 0.0 : fpsCalcInt;
	fpsCalcInt = (fpsCalcInt > 10.0) ? 10.0 : fpsCalcInt;
	if (elapsed_time > fpsCalcInt) {
		fps = sd_count / elapsed_time;
		sd_startTime = d_curTime;
		sd_count = 0.0;
	
	}
}
