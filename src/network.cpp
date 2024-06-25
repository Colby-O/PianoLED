#include "network.hpp"

#include <cstdlib>
#include <unistd.h>
#include <netinet/tcp.h>
#include <fcntl.h>

#include <iostream>

static void setNonBlocking(int sockfd) {
	int flags = ::fcntl(sockfd, F_GETFL, 0);
	if (flags == -1) {
		std::perror("fcntl F_GETFL");
		std::exit(EXIT_FAILURE);
	}

	flags |= O_NONBLOCK;
	if (fcntl(sockfd, F_SETFL, flags) == -1) {
		std::perror("fcntl F_SETFL");
		std::exit(EXIT_FAILURE);
	}
}

void Network::reconnect() {
	unsigned int length = sizeof(m_client);
	m_conn = ::accept(m_fd, (struct sockaddr*) &m_client, &length);
	setNonBlocking(m_conn);

	m_read = 0;
}

Network::Network(int port) : m_port(port) {
	m_fd = ::socket(AF_INET, SOCK_STREAM, 0);

	m_addr = {0};
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = INADDR_ANY;
	m_addr.sin_port = ::htons(m_port);

	::bind(m_fd, (struct sockaddr*) &m_addr, sizeof(m_addr));

	::listen(m_fd, 1);
	
	reconnect();
}

std::vector<char> Network::receive() {
	if (m_read == 0 || m_read < m_data[0]) {
		int read = ::read(m_conn, &m_data[m_read], sizeof(m_data));
		if (read < 0) return {};
		if (read == 0) {
			reconnect();
			return {};
		}
		m_read += read;
	}

	if (m_read < m_data[0]) return {};
	
	int packetSize = m_data[0];

	std::vector<char> res(&m_data[1], &m_data[packetSize]);

	m_read -= packetSize;

	for (int i = 0; i < m_read; i++) {
		m_data[i] = m_data[i + packetSize];
	}

	return res;
}
