#include "piano.hpp"
#include "color.hpp"
#include "music.hpp"
#include "time.hpp"
#include "ws2812-rpi.h"

Piano::Piano() : 
	strip(new NeoPixel(288)), 
	m_keyToLED(Music::generateKeyMap()),
	m_effect(new RainbowEffect())
{
	strip->setBrightness(0.5);

	for (int i = 0; i < 128; i++) {
		m_keys[i] = {
			m_keyToLED.contains(i - 21) ? m_keyToLED[i - 21] : -1,
			i,
			0,
			false,
			0,
			false
		};
	}
}

Piano::~Piano() {}

void Piano::setEffect(int e) {
	m_effect = createEffect(e);
}

void Piano::updateKeyState(int key, int vel, bool isPressed) {
	m_keys[key].hasChanged = isPressed != m_keys[key].isPressed;
	m_keys[key].isPressed = isPressed;
	m_keys[key].lastPressed = Time::getTimeMS();
	m_keys[key].vel = vel;
}

void Piano::update() {
	for (int i = 0; i < 128; i++) m_effect->update(m_keys[i]);
	for (int i = 0; i < 128; i++) {
		if (m_keys[i].led == -1) continue;
		Color col =  m_effect->getColor(m_keys[i], m_theme);
		col.RGB();
		strip->setPixelColor(m_keys[i].led, col.r, col.g, col.b);
		m_keys[i].hasChanged = false;
	}
	strip->show();
}

