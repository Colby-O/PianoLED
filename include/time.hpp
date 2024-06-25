#ifndef TIME_HPP_
#define TIME_HPP_

namespace Time {
	extern double deltaTime;

	double getTime();
	long getTimeMS();

	void startDeltaTime();
	void tickDeltaTime();
};

#endif
