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

	for (int i = 0; i <= NUM_OCTAVES; i++) 
	{
		int led = (
			FIRST_A_LED + 
			i * LEDS_PER_OCTAVE +
			((i >= SOLDERED_OCTAVE + 1) ? -1 : 0)
		);

		keyToLED.insert({i * OCTAVE_SIZE + 0,  led});
		led += FIRST_Bb_LED - FIRST_A_LED;
		keyToLED.insert({i * OCTAVE_SIZE + 1,  led});
		led += FIRST_B_LED - FIRST_Bb_LED;
		keyToLED.insert({i * OCTAVE_SIZE + 2,  led});
		led += FIRST_C_LED - FIRST_B_LED;
		keyToLED.insert({i * OCTAVE_SIZE + 3,  led});
		led += FIRST_Db_LED - FIRST_C_LED;
		keyToLED.insert({i * OCTAVE_SIZE + 4,  led});
		led += FIRST_D_LED - FIRST_Db_LED;
		keyToLED.insert({i * OCTAVE_SIZE + 5,  led});
		led += FIRST_Eb_LED - FIRST_D_LED;
		keyToLED.insert({i * OCTAVE_SIZE + 6,  led});
		led += FIRST_E_LED - FIRST_Eb_LED;
		keyToLED.insert({i * OCTAVE_SIZE + 7,  led});
		led += FIRST_F_LED - FIRST_E_LED;
		keyToLED.insert({i * OCTAVE_SIZE + 8,  led});
		led += FIRST_Gb_LED - FIRST_F_LED + ((i == SOLDERED_OCTAVE) ? -1 : 0);
		keyToLED.insert({i * OCTAVE_SIZE + 9,  led});
		led += FIRST_G_LED - FIRST_Gb_LED;
		keyToLED.insert({i * OCTAVE_SIZE + 10, led});
		led += FIRST_Ab_LED - FIRST_G_LED;
		keyToLED.insert({i * OCTAVE_SIZE + 11, led});
	}

	return keyToLED;
}
