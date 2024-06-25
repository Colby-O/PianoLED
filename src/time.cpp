#include "time.hpp"

#include <sys/time.h>

double Time::deltaTime = 0;

static double s_prevTime = 0;

double Time::getTime() {
	struct timeval tv;
	::gettimeofday(&tv, nullptr);
	double f = (tv.tv_sec);
	f += ((double)tv.tv_usec) / 1000000.0;
	return f;
}

long Time::getTimeMS() {
	struct timeval tv;
	::gettimeofday(&tv, nullptr);
	return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

void Time::startDeltaTime() {
	s_prevTime = Time::getTime();
	Time::deltaTime = 0;
}

void Time::tickDeltaTime() {
	double time = Time::getTime();
	Time::deltaTime = time - s_prevTime;
	s_prevTime = time;
}
