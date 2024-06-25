#include "app.hpp"

#include <iostream>

App::App(int port) : m_network(port) {}

App::~App() {}

void App::run() {
	while (true) {
		char* packet = m_network.receive();
		while (packet != nullptr) {
			std::cout << "vel: " << (int)packet[2] << " key: " << (int)packet[1] << " type : " << (int)packet[0] << std::endl; 
			m_piano.updateKeyState(packet[1], packet[2], packet[0]);    
			delete[] packet;
			packet = m_network.receive();
		}
		m_piano.update();    
	}
}
