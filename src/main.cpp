#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <map>

#include "ws2812-rpi.h"

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

NeoPixel* n;
std::map<int, int> keyToLED;


std::map<int, int> generateKeyMap() 
{
	std::map<int, int> keyToLED;

	for (int i = 0; i <= NUM_OCTAVES; i++) 
	{
		int led = (
			FIRST_A_LED + 
			std::floor(i * LEDS_PER_OCTAVE) +
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

bool isBlackKey(int k) 
{	
	k %= 12;
	return k == 1 || k == 3 || k == 6 || k == 8 || k == 10;
}

int processLEDs(int com, int key, int vel) 
{
	if (com == 0) n->setPixelColor(keyToLED[key - 21], 0, 0, 0);
	else {
		int b = vel;

		if (isBlackKey(key)) n->setPixelColor(keyToLED[key - 21], b, 0, 0);
		else n->setPixelColor(keyToLED[key - 21], 0, b, 0);
	}

	n->show();
}

int main(void)
{

	std::cout << "Starting..." << std::endl;

	n = new NeoPixel(288);

	keyToLED = generateKeyMap();


	for (int i = 0; i < 88; i++) {
		n->setPixelColor(keyToLED[i] , 0, 0, 0);
	}

	n->show();

	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	addr.sin_port = ::htons(6789);

	::bind(fd, (struct sockaddr*) &addr, sizeof(addr));

	::listen(fd, 1);


	struct sockaddr_in client;
	unsigned int length = sizeof(client);
	int conn = ::accept(fd, (struct sockaddr*) &client, &length);
	
	int read = 0;
	char data[128];

	while (true) 
	{
		read += ::read(conn, data, sizeof(data));
		
		while (read >= 3) 
		{

			int com = data[0];
			int key = data[1];
			int vel = data[2];

			std::cout << "Com: " << com << " Key: " << key << " Vel: " << vel << std::endl;		

			processLEDs(com, key, vel);

			read -= 3; 

			for (int i = 0; i < read; i++) 
			{
				data[i] = data[i + 3];
			}
		}
	}

	delete n;

	return EXIT_SUCCESS;	
}
