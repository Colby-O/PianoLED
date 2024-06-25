#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <map>

namespace Music {

	inline bool isBlackKey(int key) {
		key %= 12;
		return key == 1 || key == 3 || key == 6 || key == 8 || key == 10;
	}

	std::map<int, int> generateKeyMap(); 
}

#endif
