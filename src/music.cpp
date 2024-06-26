#include "music.hpp"

#include <vector>
#include <algorithm>
#include <utility>

#define SOLDERED_OCTAVE 4

const int firstLed = 3;
const std::vector<std::pair<int, int>> shiftPoints = {
	{Music::noteNameToKeyId("F#4"), -1},
};

std::map<int, int> Music::generateKeyMap() 
{
	std::map<int, int> keyToLED;

	int shift = 0;
	for (int i = 0; i < 88; i++) {
		if (
				auto shiftPoint = std::find_if(
					shiftPoints.begin(), shiftPoints.end(), [i](auto sp){ return i == sp.first; }
				);
				shiftPoint != shiftPoints.end()
		) {
			shift += shiftPoint->second;
		}
		keyToLED[i] = i * 2 + firstLed + shift;
	}

	return keyToLED;
}
