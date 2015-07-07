#pragma once

#include <stdint.h>
#include "EvThread.h"
#include <ev++.h>

class Connector : public EvThread
{
public:
	Connector(uint16_t port);
protected:
	uint16_t port;
	ev::io connect_watcher;
	int socket_d;

	virtual void init();
	virtual void finalize();
	virtual void on_stop();

	void connnect(ev::io &w, int revents);
	void handle(int client_socket);
};
