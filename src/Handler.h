#pragma once

#include "Thread.h"
#include <ev++.h>
#include <atomic>

class Server;

class Handler : public Thread
{
public:
	Handler(Server *server);
	virtual void stop();
	void stop_signal();
protected:
	virtual void init();
	virtual void finalize();
	virtual void on_stop();
	virtual void run();
	void handle(int socket);

	Server *server;
private:
	volatile std::atomic<bool> is_run;
};
