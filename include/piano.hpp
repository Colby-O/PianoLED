#ifndef PIANO_HPP_
#define PIANO_HPP_

#include "effect.hpp"
#include "key.hpp"

#include <map>
#include <memory>

class NeoPixel;

class Piano {
public:

	Piano();
	~Piano();

	void updateKeyState(int key, int vel, bool isPressed);
	void update();

	Piano(const Piano&) = delete;
	Piano& operator=(const Piano&) = delete;

private:
	Key m_keys[128];
	std::map<int, int> m_keyToLED;    
	std::unique_ptr<Effect> m_effect;
	Theme m_theme;
	
	std::unique_ptr<NeoPixel> strip; 

	void generateKeyMap();
};

#endif 
