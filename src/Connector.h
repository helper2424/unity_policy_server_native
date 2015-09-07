#pragma once

#include <stdint.h>
#include "EvThread.h"
#include <ev++.h>
#include <atomic>

class Connector : public EvThread
{
public:
	Connector(uint16_t port);
protected:
	uint16_t port;
	ev::io connect_watcher;
	ev::timer reporter;
	int socket_d;

	std::atomic<uint64_t> handled_clients;

	virtual void init();
	virtual void finalize();
	virtual void on_stop();

	void connnect(ev::io &w, int revents);
	void report();
};
