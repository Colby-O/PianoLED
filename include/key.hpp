#ifndef KEY_HPP_
#define KEY_HPP_

struct Key {
	int led;
	int id;
	int vel;
	bool isPressed;
	long lastPressed;
	bool hasChanged;
};

#endif
