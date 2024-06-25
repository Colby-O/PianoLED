#ifndef APP_HPP_
#define APP_HPP_

#include "piano.hpp"
#include "network.hpp"

class App {
public:
	App(int port);
	~App();

	App(const App&) = delete;
	App& operator=(const App&) = delete;

	void run();
private:
	Network m_network;
	Piano m_piano;
};

#endif
