#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <cstdint>
#include <tuple>

struct Color {
	std::uint8_t r;
	std::uint8_t g;
	std::uint8_t b;

	Color (std::int8_t r, std::uint8_t g, std::uint8_t b) : r(r), g(g), b(b) {};
	Color (std::uint8_t b) : Color(b, b, b) {};
	Color(void) : Color(0) {};

	static std::tuple<float, float, float> RBGtoHSV(Color col);
	static Color HSVtoRBG(float h, float s, float v);
};

#endif
