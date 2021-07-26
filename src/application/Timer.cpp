#include "Timer.h"

using namespace std::chrono;

Timer::Timer()
{
	start_time_ = GetCurrentTime();
}

long double Timer::start_time()
{
	return start_time_;
}

long double Timer::GetElapsedTime()
{
	long double current_time = GetCurrentTime();

	return current_time - start_time_;
}

long double Timer::GetCurrentTime()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
