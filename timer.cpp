#include <chrono>
#include "timer.h"

using namespace std::chrono;

high_resolution_clock::time_point start_time;

namespace Timer
{
void Start()
{
	start_time = high_resolution_clock::now();
}

int Stop()
{
	return duration_cast<milliseconds>(high_resolution_clock::now() - start_time).count();
}
}
