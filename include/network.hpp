#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <sys/socket.h>
#include <netinet/in.h>

class Network {
public:
	Network(int port);
	~Network() {}

	Network(const Network&) = delete;
	Network& operator=(const Network&) = delete;
	
	char* receive();
private:
	int m_port;
	int m_fd;
	struct sockaddr_in m_addr;
	struct sockaddr_in m_client;
	int m_conn;
	int m_read = 0;
	char m_data[2048];
	
	bool reveiveReady();
	void reconnect();
};

#endif
