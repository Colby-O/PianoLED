#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include "utils.hpp"

#include <map>
#include <string_view>
#include <vector>
#include <algorithm>
#include <utility>
#include <array>

namespace Music {
	inline bool isBlackKey(int key) {
		key %= 12;
		return key == 1 || key == 3 || key == 6 || key == 8 || key == 10;
	}

	constexpr std::array<std::pair<int, std::string_view>, 21> noteNames = {{
		{0, "B#"},
		{0, "C"},
		{1, "C#"},
		{1, "Db"},
		{2, "D"},
		{3, "D#"},
		{3, "Eb"},
		{4, "E"},
		{4, "Fb"},
		{5, "E#"},
		{5, "F"},
		{6, "F#"},
		{6, "Gb"},
		{7, "G"},
		{8, "G#"},
		{8, "Ab"},
		{9, "A"},
		{10, "A#"},
		{10, "Bb"},
		{11, "B"},
		{11, "Cb"}
	}};

	constexpr int noteNameToKeyId(std::string_view key) {
		std::size_t numPos = 0;
		while (numPos < key.length() && !Utils::isDigit(key[numPos])) numPos++;
		if (numPos == key.length()) return 0;
		int octave = key[numPos] - '0';
		std::string_view note_name = key.substr(0, key.length() - 1);
		int note = std::find_if(
			noteNames.begin(), noteNames.end(),
			[note_name](auto p) { return p.second == note_name; }
		)->first;
		return octave * 12 + note - 9;
	}

	std::map<int, int> generateKeyMap(); 
}

#endif
