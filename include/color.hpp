#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <cstdint>
#include <tuple>

struct Color {
	bool isRGB;
	union {
		struct {
			std::uint8_t r;
			std::uint8_t g;
			std::uint8_t b;
		};
		struct {
			double h;
			double s;
			double v;
		};
	};

	Color (std::int8_t r, std::uint8_t g, std::uint8_t b) : isRGB(true), r(r), g(g), b(b) {};
	Color (bool, double h, double s, double v) : isRGB(false), h(h), s(s), v(v) {};
	Color (std::uint8_t b) : Color(b, b, b) {};
	Color(void) : Color(0) {};

	Color(const Color& col) {
		this->isRGB = col.isRGB;

		if (col.isRGB) {
			this->r = col.r;
			this->g = col.g;
			this->b = col.b;
		}
		else {
			this->h = col.h;
			this->s = col.s;
			this->v = col.v;
		}
	}

	Color& HSV();
	Color& RGB();

	Color clone() const {
		if (this->isRGB) return Color(r, g, b);
		else return Color(true, h, s, v);
	}
};

#endif
