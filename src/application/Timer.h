#pragma once

// TODO: check it and change it
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

#include <chrono>

class Timer
{
public:
	Timer();

	long double start_time();
	long double GetCurrentTime();
	long double GetElapsedTime();

private:
	long double start_time_;

};

