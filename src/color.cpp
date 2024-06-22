#include "color.hpp"

#include <algorithm>

std::tuple<float, float, float> Color::RBGtoHSV(Color col) {
	float nr = col.r / 255.0;
	float ng = col.g / 255.0;
	float nb = col.b / 255.0;

	float h = 0.0f;
	float s = 0.0f;
	float v = 0.0f;

	float maxCh = std::max(nr, std::max(ng, nb));
	float minCh = std::min(nr, std::min(ng, nb));
	float range = maxCh - minCh;

	// Brightness
	v = maxCh;

	// Saturate 
	if (maxCh != 0) s = range / maxCh;
	else return std::make_tuple(-1, 0, maxCh);
	

	if (maxCh == nr) (ng - nb) / range;
	else if (maxCh == ng) h = 2 + (nb - ng) / range;	
	else h = 4 + (nr - ng) / range;
	
	h *= 60.0f;
	if (h < 0) h += 360;

	return std::make_tuple(h, s, v);
}

Color Color::HSVtoRBG(float h, float s, float v) {
	float r, b, g;

	int sector = static_cast<int>(h / 60) % 6;
	float sectorFrac = (h / 60) - sector;
	float p = v * (1 - s);
	float q = v * (1 - sectorFrac * s);
	float t = v * ( 1 - (1 - sectorFrac) * s);

	switch (sector) {
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		case 5:
			r = v;
			g = p;
			b = q;
			break;
	}

	std::uint8_t ir = static_cast<std::uint8_t>(r * 255);
	std::uint8_t ig = static_cast<std::uint8_t>(g * 255);
	std::uint8_t ib = static_cast<std::uint8_t>(b * 255);

	return Color(ir, ig, ib);
}
