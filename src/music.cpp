#include "music.hpp"

#define SOLDERED_OCTAVE 4

#define FIRST_A_LED 4
#define FIRST_B_LED 8
#define FIRST_C_LED 10
#define FIRST_D_LED 14
#define FIRST_E_LED 18
#define FIRST_F_LED 20
#define FIRST_G_LED 24

#define FIRST_Bb_LED 6
#define FIRST_Db_LED 12
#define FIRST_Eb_LED 16
#define FIRST_Gb_LED 22
#define FIRST_Ab_LED 26

#define NUM_OCTAVES 7.0
#define OCTAVE_SIZE 12.0
#define LEDS_PER_OCTAVE (FIRST_Ab_LED - FIRST_A_LED + 2)

std::map<int, int> Music::generateKeyMap() 
{
	std::map<int, int> keyToLED;

	for (int i = 0; i < 88; i++) {
		if (i < 33) keyToLED[i] = i * 2 + 3;
		else keyToLED[i] = i * 2 + 3 - 1;
	}

	return keyToLED;
}
