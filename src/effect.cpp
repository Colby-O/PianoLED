#include "effect.hpp"
#include "music.hpp"

#include <cmath>

void DefaultEffect::update(const Key& key) {}

Color DefaultEffect::getColor(const Key& key, const Theme& theme) {
	Color col;
	if (key.isPressed) {

		if (Music::isBlackKey(key.id)) {
			col = theme.colors[1];
		}
		else {
			col = theme.colors[2];
		}
		col.HSV().v = key.vel / 127.0f;
	}
	else {
		col = theme.colors[0];
	}

	return col.RGB();
}
