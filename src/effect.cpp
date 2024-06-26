#include "effect.hpp"

#include "music.hpp"
#include "time.hpp"

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

void FadeOutEffect::update(const Key& key) {
	if (key.hasChanged && key.isPressed) {
		m_keys[key.id] = 1.0;
	} else if (!key.isPressed) {
		m_keys[key.id] -= m_releaseRate * Time::deltaTime;
		if (m_keys[key.id] < 0) m_keys[key.id] = 0;
	}
}

Color FadeOutEffect::getColor(const Key& key, const Theme& theme) {
	Color col;
	if (Music::isBlackKey(key.id)) {
		col = theme.colors[1];
	}
	else {
		col = theme.colors[2];
	}
	col.HSV().v *= m_keys[key.id];

	return col.RGB();
}

void RainbowEffect::update(const Key& key) {
}

Color RainbowEffect::getColor(const Key& key, const Theme& theme) {
	m_rot += Time::deltaTime * m_rotRate;
	return Color(
		true,
		std::fmod((double)key.id * (360.0 / 88.0) * m_rotRate + m_rot, 360.0),
		1,
		0.15
	);
}


