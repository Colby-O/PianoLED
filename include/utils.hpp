#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <sys/time.h>

namespace Utils {
	inline long getTimeInMS() {
		struct timeval tv;
		::gettimeofday(&tv, NULL);
		return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	}
}

#endif
