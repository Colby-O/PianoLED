#include "app.hpp"

#include "time.hpp"

#include <iostream>

#include <unistd.h>

App::App(int port) : m_network(port) {}

App::~App() {}

void App::run() {
	Time::startDeltaTime();
	int effect = 0;
	while (true) {
		std::vector<char> packet = m_network.receive();
		while (packet.size() > 0) {
			if (packet[0] == 2) {
				effect = (effect + 1) % 3;
				m_piano.setEffect(effect);
			} else {
				std::cout << "vel: " << (int)packet[2] << " key: " << (int)packet[1] << " type : " << (int)packet[0] << std::endl; 
				m_piano.updateKeyState(packet[1], packet[2], packet[0]);    
			}
			packet = m_network.receive();
		}
		m_piano.update();
		::usleep(5000);
		Time::tickDeltaTime();
	}
}
